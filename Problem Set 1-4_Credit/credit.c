#include <stdio.h>
#include <math.h>
#include <cs50.h>

// AMEX: 15 digits, starts with 34/37
// MasterCard: 16 digits, starts with 51~55
// Visa: 13/16 digits, starts with 4

// 1. Multiply every other digit by 2, starting with the number???s second-to-last digit, and then add those products??? digits together.
// 2. Add the sum to the sum of the digits that weren???t multiplied by 2.
// 3. If the total???s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

int card_lenghth_counter(long long card_num);
int sum1(long long card_num);
int sum2(long long card_num);
bool card_valid_check(int sum1, int sum2);
string card_company_check(long long card_num, int card_length);

int main(void)
{
    long long card_num;
    do
    {
        card_num = get_long("Your Card Numbuer is: ");
    } while (card_num < 0);

    int card_length = card_lenghth_counter(card_num);
    string final_result = card_company_check(card_num, card_length);
    if (card_valid_check(sum1(card_num), sum2(card_num)))
    {
        printf("%s\n", final_result);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Count the length of card_num
int card_lenghth_counter(long long card_num)
{
    int count = 0;
    while (card_num > 0)
    {
        card_num /= 10;
        count++;
    }
    return count;
}

// Sum the digit that weren't multiplied
int sum1(long long card_num)
{
    int i = 0;
    int sum = 0;
    while (pow(10, i) < card_num)
    {
        long long pow1 = pow(10, i + 1) + 0.5;
        long long pow2 = pow(10, i) + 0.5;
        sum = sum + (card_num % pow1 / pow2);
        i += 2;
    }
    return sum;
}

// Sum the digit that needs to be multiplied by 2
int sum2(long long card_num)
{
    int i = 1;
    int sum = 0;
    int temp_sum = 0;
    while (pow(10, i - 1) < card_num)
    {
        long long pow1 = pow(10, i + 1) + 0.5;
        long long pow2 = pow(10, i) + 0.5;
        temp_sum = card_num % pow1 / pow2 * 2;
        if (temp_sum >= 10)
        {
            temp_sum = (temp_sum / 10) + (temp_sum % 10);
        }
        sum = sum + temp_sum;
        i += 2;
    }
    return sum;
}

bool card_valid_check(int sum1, int sum2)
{
    int check_sum;
    check_sum = sum1 + sum2;
    if (check_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string card_company_check(long long card_num, int card_length)
{
    string card_company;
    int card_num_start = card_num / (pow(10, card_length - 2) + 0.5);
    if (card_length == 15 && (card_num_start == 34 || card_num_start == 37))
    {
        card_company = "AMEX";
    }
    else if (card_length == 16 && card_num_start >= 51 && card_num_start <= 55)
    {
        card_company = "MASTERCARD";
    }
    else if ((card_length == 13 || card_length == 16) && card_num_start / 10 == 4)
    {
        card_company = "VISA";
    }
    else
    {
        card_company = "INVALID";
    }
    return card_company;
}
