#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

Interp4Set::Interp4Set(): _Objekt_s(""), _Wsp_x(0), _Wsp_y(0), _Angle(0)
{}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  printf("%s %s %lf %lf %lf\n", GetCmdName(), _Objekt_s.c_str(), _Wsp_x, _Wsp_y, _Angle); 
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Objekt_s;
  Strm_CmdsList >> _Wsp_x;
  Strm_CmdsList >> _Wsp_y;
  Strm_CmdsList >> _Angle;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set Nazwa_obiektu Wsp_x Wsp_y kat" << endl;
}
