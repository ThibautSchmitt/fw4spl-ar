/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __IOIGTL_SOPENIGTLINKSENDER_HPP__
#define __IOIGTL_SOPENIGTLINKSENDER_HPP__

#include "ioIGTL/config.hpp"

#include <fwTools/Failed.hpp>
#include <fwCom/Slot.hpp>
#include <fwCom/Slots.hpp>
#include <fwData/Object.hpp>
#include <igtlNetwork/Client.hpp>
#include <igtlNetwork/Server.hpp>
#include <ioNetwork/INetworkSender.hpp>
#include <fwThread/Worker.hpp>

#include <boost/type.hpp>
#include <boost/thread.hpp>

#include <string>

namespace ioIGTL
{

/**
 * @brief Service to create an OpenIGTLink Server
 *
 * @section XML XML Configuration
 * @code{.xml}
 * <service uid="..." type="::ioIGTL::SOpenIGTLinkSender" >
 *      <port>...</port>
 *      <deviceName>...</deviceName>
 *      <in group="objects">
 *           <key uid="..." />
 *           <key uid="..." />
 *      </in>
 * </service>
 * @endcode
 * @subsection Input Input
 * - \b objects [::fwData::Object]: defines the objects to send.
 * @subsection Configuration Configuration:
 * - \b port : defines the port where the objects will be sent
 * - \b deviceName : defines the name of the device (here, our server)
**/

class IOIGTL_CLASS_API SOpenIGTLinkSender : public ::ioNetwork::INetworkSender
{

public:

    fwCoreServiceClassDefinitionsMacro ( (SOpenIGTLinkSender)( ::ioNetwork::INetworkSender ) );

    IOIGTL_API static const ::fwCom::Slots::SlotKeyType s_UPDATE_CONFIGURATION_SLOT;
    typedef ::fwCom::Slot< void (::boost::uint16_t const) > UpdateConfigurationSlotType;

    IOIGTL_API static const ::fwCom::Slots::SlotKeyType s_START_SENDING_SLOT;
    typedef ::fwCom::Slot< void () > StartSendingSlotType;

    IOIGTL_API static const ::fwCom::Slots::SlotKeyType s_STOP_SENDING_SLOT;
    typedef ::fwCom::Slot< void () > StopSendingSlotType;

    /// Constructor
    IOIGTL_API SOpenIGTLinkSender();


    /// Destructor
    IOIGTL_API virtual ~SOpenIGTLinkSender();

protected:

    IOIGTL_API virtual void configuring() throw ( ::fwTools::Failed );

    /**
     * @brief start the server. This method block actually
     */
    IOIGTL_API virtual void starting() throw ( ::fwTools::Failed );

    /**
     * @brief stop the server
     */
    IOIGTL_API virtual void stopping() throw ( ::fwTools::Failed );

    /**
     * @brief change the port of the server use it before start
     */
    IOIGTL_API void setPort(boost::uint16_t const port) throw (::fwTools::Failed);


private:

    /**
     * @brief slot called when configuration of sender is updated
     *
     * @see ioNetwork::INetworkSender
     */
    void updateConfiguration(::boost::uint16_t const port);

    /// Starts the server
    IOIGTL_API void startSending();

    /// Stops the server
    IOIGTL_API void stopSending();

    /**
     * @brief method to send data. Linked to m_slotSendData
     *
     * @param[in] obj obj to send
     */
    IOIGTL_API void sendObject(const ::fwData::Object::sptr& obj);

    /// Server instance
    ::igtlNetwork::Server::sptr m_server;

    /// Port to listen
    ::boost::uint16_t m_port;

    /// Worker smart pointer to run the server loop in a separate thread
    ::fwThread::Worker::sptr m_serverWorker;

    ///Slot to update configuration
    UpdateConfigurationSlotType::sptr m_updateConfigurationSlot;

    ///Slot to start sending
    StartSendingSlotType::sptr m_startSendingSlot;

    ///Slot to stop sending
    StopSendingSlotType::sptr m_stopSendingSlot;

    ///True is server is sending
    bool m_isSending;

    ///device name
    std::string m_deviceName;
};



} // namespace ioIGTL

#endif /*__IOIGTL_SOPENIGTLINKSENDER_HPP__*/
