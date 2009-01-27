/** @doc Object to interact with the SoT.

   CVS Information:
   $Id$
   $Author$
   $Date$
   $Revision$
   $Source$
   $Log$

   Copyright (c) 2009
   @author Olivier Stasse
   
   JRL-Japan, CNRS/AIST

   All rights reserved.
   
   Redistribution and use in source and binary forms, with or without modification, 
   are permitted provided that the following conditions are met:
   
   * Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
   * Neither the name of the CNRS and AIST nor the names of its contributors 
   may be used to endorse or promote products derived from this software without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS 
   OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
   AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
   IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _CONNECTION_TO_SOT_H_
#define _CONNECTION_TO_SOT_H_

#ifdef OMNIORB4
#include <omniORB4/CORBA.h>
#include "ServerCommand.hh"
#endif


namespace llvs
{
  class LowLevelVisionServer;
  class ConnectionToSot
    {
      
    public:

      /*! \brief Constructor */
      ConnectionToSot(LowLevelVisionServer * aLLVS);

      /*! \brief Destructor*/
      ~ConnectionToSot();

      /*! \brief Read waist values.*/
      void ReadWaistSignals(double waistposition[3],
			    double waistattitude[3]);

      /*! \brief Create the signals, and plkug them. */
      bool Init();

      /* ! Start the thread */
      void StartThreadOnConnectionSot();

      /* ! Stop the thread */
      void StopThreadOnConnectionSot();


      /*! Internal method to set corba reference */
      bool SetCorbaReference();

    private:
      
      /*! Pointer on LLVS server. */
      LowLevelVisionServer * m_LLVS;

      /*! Pointer on SoT server. */
      SOT_Server_Command_var m_SOT_Server_Command;

      /*! \brief Store the rank of waist position signal. */
      CORBA::Long m_WaistPositionSignalRank;

      /*! \brief Store the rank of waist attitude signal. */
      CORBA::Long m_WaistAttitudeSignalRank;

      /*! \brief Boolean value to go out of the thread */
      bool m_EndOfThreadLoop;

    protected:

    public:
      /* ! \brief To know if the thread should be stop or not */
      bool GetEndOfThreadLoop() const;

    };
};

#endif /* _CONNECTION_TO_SOT_H_ */
