#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
//#include "misc/ConsoleUtils.h"
#include "EntityNames.h"
#include "Bandit.h"

std::ofstream os;
using std::cout;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
    os.open("output.txt");
#endif

    //seed random number generator
    srand((unsigned) time(NULL));

    //create a miner
    Miner* Bob = new Miner(ent_Miner_Bob);

    //create his wife
    MinersWife* Elsa = new MinersWife(ent_Elsa);

    Bandit* bandit = new Bandit(ent_Bandit);

    //register them with the entity manager
    EntityMgr->RegisterEntity(Bob);
    EntityMgr->RegisterEntity(Elsa);
    EntityMgr->RegisterEntity(bandit);
    //run Bob and Elsa through a few Update calls
    for (int i=0; i<30; ++i)
    {

        cout << "\n" <<"Money Carried\n" << "Bob: " << Bob->GoldCarried() << "\n" << "bandit:" << bandit->GoldCarried() << "\n";


        Bob->Update();
        Elsa->Update();
        bandit->Update();

        //Second step added
        Bob->UpdateStateAndLocation();
        Elsa->UpdateStateAndLocation();
        bandit->UpdateStateAndLocation();

        //dispatch any delayed messages
        Dispatch->DispatchDelayedMessages();

        std::cout << "\n" ;

        system("pause");
        //Sleep(800);
    }

    //tidy up
    delete Bob;
    delete Elsa;
    delete bandit;

    //wait for a keypress before exiting
    //PressAnyKeyToContinue();


    return 0;
}






