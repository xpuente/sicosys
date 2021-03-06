//
// Copyright (C) 1998-2001 by ATC Group, the University of 
//    Cantabria, Spain.
// 
// This file is part of the Sicosys distribution. 
// See LICENSE file for terms of the license. 
//
//
//*************************************************************************
//
// File: ../ATCSimul/inc/PRZRoutingAdaptativeBurbleFlowMuxed.hpp
//
// Description:  fichero de encabezado de la clase "PRZRoutingAdaptativeBurbleFlowMuxed"
//
// Notes:  
//
// $Author: vpuente $ 
//
// $RCSfile: PRZRoutingAdaptativeBurbleFlowMuxed.hpp,v $
//
// $Date: 2001/10/08 05:43:07 $
//
// $Revision: 1.1.1.1 $
//
//*************************************************************************

#ifndef __PRZRoutingAdaptativeBurbleFlowMuxed_HPP__
#define __PRZRoutingAdaptativeBurbleFlowMuxed_HPP__

//*************************************************************************

   #include <PRZRoutingFlow.hpp>

   #ifndef __PRZTable_HPP__
   #include <PRZTable.hpp>
   #endif
   
   #ifndef __PRZMessage_HPP__
   #include <PRZMessage.hpp>
   #endif
   
   #ifndef __PRZSequence_HPP__
   #include <PRZSequence.hpp>
   #endif   
   
//*************************************************************************

   typedef PRZQueueTable<PRZMessage*> TMessagesQueue;
   typedef PRZSequence<unsigned> TInterfazList;
//*************************************************************************

   class PRZFifoMemory;
   
//*************************************************************************

   class PRZRoutingAdaptativeBurbleFlowMuxed : public PRZRoutingFlow
   {
      typedef PRZRoutingFlow Inhereited;
      enum { Free, WaitingHeader, DataTx, WaitCrossbarRx };

   public:
      PRZRoutingAdaptativeBurbleFlowMuxed( PRZComponent& component);
      ~PRZRoutingAdaptativeBurbleFlowMuxed();

      virtual void    postInitialize();
      virtual Boolean outputWriting();
      virtual Boolean controlAlgoritm(Boolean info=false, int delta=0);
      virtual Boolean onReadyUp(unsigned interfaz, unsigned cv);
      virtual Boolean onReadyDown(unsigned interfaz, unsigned cv);
      virtual Boolean onStopUp(unsigned interfaz, unsigned cv);
      virtual Boolean onStopDown(unsigned interfaz, unsigned cv);

      virtual PRZString getStatus() const;
            
      // Run time information
      DEFINE_RTTI(PRZRoutingAdaptativeBurbleFlowMuxed);
      
   protected:
      virtual Boolean dispatchEvent(const PRZEvent& event);
      virtual Boolean updateMessageInfo(PRZMessage* msg);
      przROUTINGTYPE  getOppositeRoutingType(int delta) const;
      przROUTINGTYPE  getDirectRoutingType(int delta) const;
      virtual Boolean createMessageRequest(PRZMessage** msg, unsigned interfaz);
      void            addHeaderReceived(PRZMessage* msg, unsigned interfaz);
      void            dataTransmit();
      void            initializeRouting();
      unsigned        getCurrentLocalPort();
      unsigned        getHeaderX() const;
      unsigned        getHeaderY() const;
      

   protected:
      PRZFifoMemory*  m_BufferXp;
      PRZFifoMemory*  m_BufferXm;
      PRZFifoMemory*  m_BufferYp;
      PRZFifoMemory*  m_BufferYm;
      unsigned        m_interfazActual;
      unsigned        m_inputs;
   
      //Alterados con respecto a la clase original
      TMessagesQueue  *m_FlitsRx;
      
      unsigned  m_CurrentOut;
      unsigned  *m_RequestState;
      unsigned  m_CurrentLocalPort;
      Boolean   m_InputStopped;      
      Boolean   m_FirstMessage;
      
      TInterfazList m_listRequest;
      Boolean       *m_listRequest_boolean;
      Boolean       m_otherRequest;
   };

//*************************************************************************


#endif


// fin del fichero
