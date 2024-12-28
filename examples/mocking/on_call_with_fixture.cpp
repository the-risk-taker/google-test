#include <gmock/gmock.h>

using ::testing::Return;

class BankServer
{
  public:
    virtual ~BankServer() {}
    virtual void Connect() = 0;
    virtual void Disconnect() = 0;
    virtual void Credit(int account_number, int value) = 0;
    virtual void Debit(int account_number, int value) = 0;
    virtual bool DoubleTransaction(int account_number, int value1, int value2) = 0;
    virtual int GetBalance(int account_number) const = 0;
};

class MockBankServer : public BankServer
{
  public:
    MOCK_METHOD(void, Connect, (), (override));
    MOCK_METHOD(void, Disconnect, (), (override));
    MOCK_METHOD(void, Credit, (int, int), (override));
    MOCK_METHOD(void, Debit, (int, int), (override));
    MOCK_METHOD(bool, DoubleTransaction, (int, int, int), (override));
    MOCK_METHOD(int, GetBalance, (int), (const, override));
};

class AtmMachine
{
    // The bank server we are talking to.
    BankServer* bankServer_;

  public:
    // Constructor.
    AtmMachine(BankServer* bankServer) : bankServer_(bankServer) {}

    // Withdraws value from account_number.
    bool Withdraw(int account_number, int value)
    {
        bool result = false;
        bankServer_->Connect();
        auto available_balance = bankServer_->GetBalance(account_number);

        if (available_balance >= value)
        {
            bankServer_->Debit(account_number, value);
            result = true;
        }

        bankServer_->Disconnect();
        return result;
    }

    void test() {}
};

class DoDefaultTest : public ::testing::Test
{
  public:
    void SetUp() override
    {
        ON_CALL(mock_bankserver_, GetBalance).WillByDefault(Return(1000));
    }

    MockBankServer mock_bankserver_;
};

TEST_F(DoDefaultTest, CanWithdraw)
{
    // Arrange
    const int account_number = 1234;
    const int withdraw_value = 1000;

    MockBankServer mock_bankserver;

    // Act
    AtmMachine atm_machine(&mock_bankserver_);
    bool withdraw_result = atm_machine.Withdraw(account_number, withdraw_value);

    // Assert
    EXPECT_TRUE(withdraw_result);
}
