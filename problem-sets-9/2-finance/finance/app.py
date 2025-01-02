import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    if request.method == "GET":
        portfolio = db.execute(
            "SELECT symbol, shares_owned FROM portfolios WHERE user_id = ? GROUP BY symbol",
            session["user_id"],
        )
        stock_list = []
        stock_balance = 0
        for stock in portfolio:
            symbol_current_price = lookup(stock["symbol"])["price"]
            stock_list.append(
                {
                    "symbol": stock["symbol"],
                    "shares_owned": stock["shares_owned"],
                    "current_price": symbol_current_price,
                }
            )
            stock_balance += symbol_current_price * stock["shares_owned"]
        user_cash_list = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        user_cash = user_cash_list[0]["cash"]
        total = user_cash + stock_balance
        return render_template(
            "index.html",
            stock_list=stock_list,
            user_cash=user_cash,
            total=total,
        )

    return redirect("/")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":

        stock_information = lookup(request.form.get("symbol"))
        try:
            stock_symbol = stock_information["symbol"]
        except:
            return apology("stock symbol is invalid")

        try:
            shares_to_buy = int(request.form.get("shares"))
        except ValueError:
            return apology("invalid number")

        stock_current_price = stock_information["price"]

        if not stock_information:
            return apology("stock symbol is invalid")

        if shares_to_buy <= 0:
            return apology("minimum bought share is 1")

        # update user's cash
        user_cash_list = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        user_cash = user_cash_list[0]["cash"]
        total_cost = shares_to_buy * stock_current_price
        if user_cash < total_cost:
            return apology("not enough money")

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            user_cash - total_cost,
            session["user_id"],
        )

        # update portfolio
        user_shares_owned_list = db.execute(
            "SELECT shares_owned FROM portfolios WHERE symbol = ? AND user_id = ?",
            stock_symbol,
            session["user_id"],
        )
        if not user_shares_owned_list:
            user_shares_owned = 0
        else:
            user_shares_owned = user_shares_owned_list[0]["shares_owned"]

        db.execute(
            "INSERT INTO portfolios (user_id, symbol, shares_owned) VALUES (?, ?, ?)"
            "ON CONFLICT(user_id, symbol) DO UPDATE SET shares_owned = ?",
            session["user_id"],
            stock_symbol,
            shares_to_buy,
            user_shares_owned + shares_to_buy,
        )

        # update transactions record
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
            session["user_id"],
            stock_symbol,
            shares_to_buy,
            stock_current_price,
        )
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        transactions = db.execute(
            "SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id=? GROUP BY timestamp DESC", session["user_id"]
        )

        transactions_dict_list = []
        for trans in transactions:
            
        return render_template("history.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # click quote after login render quote.html
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        quote = request.form.get("symbol")

        try:
            stock_information = lookup(quote)
        except:
            return apology("invalid symbol!")

        if stock_information == None:
            return apology("invalid symbol!!!")

        return render_template(
            "quoted.html",
            companyName=stock_information["name"],
            companySymbol=stock_information["symbol"],
            stockPrice=stock_information["price"],
        )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # click register or through url render register.html
    if request.method == "GET":
        return render_template("register.html")

    # submit through form
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # check username if blank
        if not username:
            return apology("username must not be blank")

        # check pw if blank
        elif not password:
            return apology("password must not be blank")
        elif password != confirmation:
            return apology("password not match")

        hash_pw = generate_password_hash(password)

        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username,
                hash_pw,
            )
        except:
            return apology("username already exists")

        return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    portfolio = db.execute(
        "SELECT symbol, shares_owned FROM portfolios WHERE user_id = ?",
        session["user_id"],
    )
    user_cash_list = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"]
    )
    user_cash = user_cash_list[0]["cash"]

    if request.method == "GET":
        symbol_list = []
        for stock in portfolio:
            symbol_list.append(stock["symbol"])
        return render_template("sell.html", symbol_list=symbol_list)

    if request.method == "POST":

        chosen_symbol = request.form.get("symbol")
        try:
            chosen_symbol_info = lookup(chosen_symbol)
        except:
            return apology("choose a valid symbol!")
        chosen_symbol_current_price = chosen_symbol_info["price"]
        shares_to_sell = int(request.form.get("shares"))
        shares_owned_list = db.execute(
            "SELECT shares_owned FROM portfolios WHERE user_id=? AND symbol=?",
            session["user_id"],
            chosen_symbol,
        )
        shares_owned = int(shares_owned_list[0]["shares_owned"])

        if not shares_to_sell:
            return apology("choose valid number of shares")
        if shares_owned < shares_to_sell:
            return apology("not sufficient shares to sell")

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
            session["user_id"],
            chosen_symbol,
            (-shares_to_sell),
            chosen_symbol_current_price,
        )

        db.execute(
            "UPDATE portfolios SET shares_owned=? WHERE user_id =? AND symbol =?",
            shares_owned - shares_to_sell,
            session["user_id"],
            chosen_symbol,
        )

        db.execute(
            "UPDATE users SET cash=? WHERE id=?",
            user_cash + (shares_to_sell * chosen_symbol_current_price),
            session["user_id"],
        )

        return redirect("/")
