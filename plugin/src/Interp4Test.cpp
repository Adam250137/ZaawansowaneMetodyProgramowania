#include <iostream>
#include "Interp4Test.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Test"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Test::CreateCmd();
}

Interp4Test::Interp4Test(){}

/*!
 *
 */
void Interp4Test::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " Parameters" << endl;
}


/*!
 *
 */
const char* Interp4Test::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Test::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Test::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Test::CreateCmd()
{
  return new Interp4Test();
}


/*!
 *
 */
void Interp4Test::PrintSyntax() const
{
  cout << "   Syntax Example" << endl;
}
