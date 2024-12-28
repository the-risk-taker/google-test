#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <ostream>

struct BankAccount
{
    int balance;

    void deposit(int amount)
    {
        balance += amount;
    }

    bool withdraw(int amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            return true;
        }

        return false;
    }
};

struct AccountState
{
    int initial_balance;
    int withdraw_amount;
    int final_balance;
    bool success;

    friend std::ostream& operator<<(std::ostream& os, const AccountState& account_state)
    {
        return os << "(initial_balance = " << account_state.initial_balance << ", withdraw_amount = " << account_state.withdraw_amount
                  << ", final_balance = " << account_state.final_balance << ", success = " << account_state.success << ")";
    }
};

struct BankAccountTest : testing::TestWithParam<AccountState>   // NOTE: BankAccountTest is test suite but parametrized
                                                                // NOTE: Use 'testing::WithParamInterface' if inheriting from existing test fixture
{
    BankAccount account;

    BankAccountTest()
    {
        account.balance = GetParam().initial_balance;
    }
};

TEST_P(BankAccountTest, Withdraw)
{
    auto account_state = GetParam();
    auto success = account.withdraw(account_state.withdraw_amount);

    EXPECT_EQ(account_state.final_balance, account.balance);
    EXPECT_EQ(account_state.success, success);
}

INSTANTIATE_TEST_SUITE_P(,
                         BankAccountTest,
                         testing::Values(   //
                             AccountState {100, 50, 50, true},
                             AccountState {100, 100, 0, true},
                             AccountState {100, 200, 100, false}));