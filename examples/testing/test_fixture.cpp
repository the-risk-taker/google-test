#include <gtest/gtest.h>

struct BankAccount
{
    int balance;

    void deposit(int amount)
    {
        balance += amount;
    }
};

struct BankAccountTest : testing::Test   // NOTE: BankAccountTest is a 'test fixture'
{
    BankAccount account;
};

TEST_F(BankAccountTest, BankAccountStartsEmpty)
{
    EXPECT_EQ(0, account.balance);
}

TEST_F(BankAccountTest, CanDepositMoney)
{
    account.deposit(100);
    EXPECT_EQ(100, account.balance);
}
