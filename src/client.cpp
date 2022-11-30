#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "AccessControl.hh"
#include "Port.hh"
#include "client.hh"

using namespace std;

/*!
 * \brief Wysyła napis do poprzez gniazdo sieciowe.
 *
 * Wysyła napis do poprzez gniazdo sieciowe.
 * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które 
 *                        ma zostać wysłany napis w sensie języka C.
 * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */
int Send(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}


/*!
 * \brief Ilość stanów każdego z obiektów.
 *
 * Ilość stanów każdego z obiektów.
 * Podział na kolejne stany obiektów wykorzystywany jest
 * do animacji ruchu obiektów.
 */
#define STATES_NUMBER   8


/*!
 * \brief Funkcja jest treścią wątku komunikacyjnego
 * 
 * Funkcja jest treścią wątku komunikacyjnego.
 * \param[in] rSender - odpowiada za śledenie zmian na scenie 
 *                      i przesyłanie do serwera graficznego
 *                      aktualnego stanu sceny, gdy uległ on zmianie.
 */
void Fun_CommunicationThread(Sender  *pSender)
{
  pSender->Watching_and_Sending();
}


/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int& rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}

/*!
 * \brief Przykład wykonywania pojedynczej operacji z animacją.
 *
 * Przykład wykonywania pojedynczej operacji z animacją.
 * \param[in] pObj - wskaźnik na obiekt, dla którego ma być wykonana dana operacja
 *                   zmiany jego stanu.
 * \param[in] pAccCtrl - wskaźnik na obiekt, poprzez który przekazywana jest informacja
 *                   o zmianie na scenie, zaś w trakcie dokonywania zmianay
 *                   zamykany jest dostęp do całej sceny.
 * \retval true - Jeśli dokonan zosała zmiana stanu wszystkich obiektów.
 * \retval false - w przypadku przeciwnym.
 */
bool ChangeState(Scene &Scn) //GeomObject *pObj, AccessControl  *pAccCtrl)
{
  return true;
}



// ----------------------------------------------------------------------------------------------------------------------------------------------------

Scene::Scene( vector<Cube> obj )
{
    _Container4Objects = obj;
}

Sender::Sender( Scene *pScn): _pScn(pScn) {

}



void Sender::Watching_and_Sending() {
    while (ShouldCountinueLooping()) {
        if (!_pScn->IsChanged())  { usleep(10000); continue; }
        _pScn->LockAccess();

        //------- Przeglądanie tej kolekcji to uproszczony przykład

        for (Cube rObj : _pScn->_Container4Objects) {
            string text = "AddObj Name=" + rObj.to_string();
            cout<<text<<endl;
            Send(0,text.c_str());
        }

        _pScn->CancelChange();
        _pScn->UnlockAccess();
    }
}

void startClient( Scene scene ){
    Sender sender( &scene );
    int Socket;
    if (!OpenConnection(Socket)) return;

    // std::thread Thread4Sending(&Sender::Watching_and_Sending, &sender);
    
    Send(Socket,"Clear\n");

    for( Cube obj: scene._Container4Objects ){
        string text = "AddObj Name=" + obj.to_string();
        cout<<text<<endl;
        Send(Socket,text.c_str());
    }

    Send(Socket,"Close\n");
}