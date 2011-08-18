#include "mfile.h"
#include "mobject.h"
#include "mevent.h"
#include "msocket.h"
#include "mserversocket.h"
#include "meventloop.h"

class Tester : public MObject
{
    M_OBJECT(Tester)
public:
    Tester()
    {
        registerInvokable(M_INVOKABLE1(Tester, doTest));
    }

    void doTest(mref serverSocket)
    {
        std::cout << "Doing test with " << serverSocket->className() << "!" << std::endl;
    }
};

int main(int argc, char **argv)
{
    Tester::MRef tester = Tester::alloc();

    MServerSocket::MRef serverSocket = MServerSocket::alloc();
    tester->invokableByName("doTest")->invoke(serverSocket);

    return 0;
}
