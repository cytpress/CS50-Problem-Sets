-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT name
FROM people -- list of people's license that exit between 10:15 to 10:25 
WHERE id IN (
        SELECT id
        FROM people
        WHERE license_plate IN(
                SELECT license_plate
                FROM bakery_security_logs
                WHERE day = 28
                    AND hour = 10
                    AND minute >= 15
                    AND minute <= 25
                    AND activity = "exit"
            )
    ) -- transaction account that location = Leggett Street 7/28
    AND id IN (
        SELECT id
        FROM people
        WHERE id IN (
                SELECT person_id
                FROM bank_accounts
                WHERE account_number IN(
                        SELECT account_number
                        FROM atm_transactions
                        WHERE month = 7
                            AND day = 28
                            AND atm_location = "Leggett Street"
                            AND transaction_type = "withdraw"
                    )
            )
    ) -- phone call on 7/28 and duration <= 60
    AND id IN(
        SELECT id
        FROM people
        WHERE phone_number IN(
                SELECT caller
                FROM phone_calls
                WHERE day = 28
                    AND duration <= 60
            )
    ) -- Passport in first flight on 7/29
    AND id IN (
        SELECT id
        FROM people
        WHERE passport_number IN (
                SELECT passport_number
                FROM passengers
                WHERE flight_id = (
                        SELECT id
                        FROM flights
                        WHERE day = 29
                        ORDER BY hour
                        LIMIT 1
                    )
            )
    );
-- Destination (first flight 7/29)
SELECT city
FROM airports
WHERE id =(
        SELECT destination_airport_id
        FROM flights
        WHERE day = 29
        ORDER BY hour
        LIMIT 1
    );
-- Accomplice 
SELECT name
FROM people
WHERE phone_number IN (
        SELECT receiver
        FROM phone_calls
        WHERE caller =(
                SELECT phone_number
                FROM people
                WHERE name = "Bruce"
            )
            AND day = 28
            AND duration <= 60
    );