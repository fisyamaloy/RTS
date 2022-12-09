#include <Client.hpp>
#include <string>

class App : public Client
{
public:
    App();

    ~App();

protected:
    void onServerAccepted() override;
    void onServerPing(double timestamp) override;
};
