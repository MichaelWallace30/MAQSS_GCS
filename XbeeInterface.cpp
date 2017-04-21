#include "XbeeInterface.hpp"


XbeeInterface::XbeeInterface(QObject *parent) : QObject(parent), commNode(GCS_NODE)
{
    qDebug() << "Instantiating single_test class";

    //CommProtocol setup and init
    //disable pinging output
    comnet::constate::ConnectionStateManager::ConStateEnabled = false;
    //**Important** this id changes for each UAV look at xbee to platform for specific address

    //load aes key
    commNode.LoadKey((char*)"NGCP project 2016");
    //commNode.LoadKeyFromFile("key.txt");

    // Allow client to suppress or unsuppress messages handled by the CommProtocol Library.
   // comnet::debug::Log::Suppress(comnet::debug::LOG_NOTIFY);
    //comnet::debug::Log::Suppress(comnet::debug::LOG_WARNING);
    //comnet::debug::Log::Suppress(comnet::debug::LOG_NOTE);

    if(USE_XBEE)
    {
      //init connection xbee
      commNode.InitConnection(ZIGBEE_LINK, "/dev/ttyUSB0", "", 57600);//XBEE PORT, NULL, xbee baudrate
      //add address xbee
      commNode.AddAddress(12, "0013A20040917A31" );;//GCS node number, GCS xbee address
      //could add more Connections
    }
    else
    {
      //init connection UDP
     // commNode.InitConnection(UDP_LINK, THIS_UDP_PORT, THIS_IP);//the uav ip and port
      //add address UDP
      //commNode.AddAddress(GCS_NODE, GCS_IP, GCS_PORT);//GCS node number, GCS IP, GCS port
    }

    commNode.LinkCallback(new ngcp::VehicleGlobalPosition(), new comnet::Callback((comnet::callback_t) &XbeeInterface::VehicleGlobalPositionCallback));
    //end CommPortocol setup and init

    qDebug() << "Finished instantiating single_test class";
}

error_t XbeeInterface::VehicleGlobalPositionCallback(const comnet::Header& header, const ngcp::VehicleGlobalPosition & vgp, comnet::Comms& node){

    qDebug() << "Entered Callback";


    QString q_str = "ID: " + QString::number(vgp.vehicle_id) +
            " longitude: " + QString::number(vgp.longitude) +
            "latitude: " + QString::number(vgp.latitude) +
            " altitude: " + QString::number(vgp.altitude);
    //emit newMsg(q_str);

}
/*
void XbeeInterface::callbackFun(XBEE::Frame *item) {

        qDebug() << "Entered Callback";
    // ReceivePacket pointeri
    // dynamic cast to type of frame I think it is (ReceivePacket), store in pointer
    XBEE::ReceivePacket *r_packet = dynamic_cast<XBEE::ReceivePacket*>(item);
    std::string str_data;



    // check if pointer is NULL
    if (r_packet != NULL) {
        qDebug() << "Starting GetData";
        str_data = r_packet->GetData();

        std::cout << "Data: " << str_data.c_str() << std::endl;
    }

    QString q_str = QString::fromUtf8(str_data.c_str());
    emit newMsg(q_str);

//    qDebug() << "Inside Here";
}
*/

/*
void XbeeInterface::writeMsg(QString msg) {
    // Assumes msg is of the form NEWMSG,TYPE,QX,....

    if (comms) {
    // Split string by , to determine target
    qDebug() << "Writing Msg: " << msg;
    QStringList list1 = msg.split(',', QString::SkipEmptyParts);
    QString target_vehicle = list1.at(2).at(1);
    unsigned int target_id = target_vehicle.toUInt();
    std::string str_data = msg.toStdString();

    // TODO: Make this less hardcoded
    XBEE::TransmitRequest frame_a(0x0013A20040A8157E);
    XBEE::TransmitRequest frame_b(0x0013A20040F8063C);
    XBEE::TransmitRequest frame_c(0x0013A20040F8064D);
    XBEE::TransmitRequest frame_d(0x0013A20040A815D6);

        qDebug() << "Target_id: " << target_id;
    // TODO: Refactor to not be hardcoded
    switch (target_id) {
    case 0:
        frame_a.SetData(str_data);
        serial_interface.AsyncWriteFrame(&frame_a);
        break;

    case 1:
        frame_b.SetData(str_data);
        serial_interface.AsyncWriteFrame(&frame_b);
        break;

    case 2:
        frame_c.SetData(str_data);
        serial_interface.AsyncWriteFrame(&frame_c);
        break;

    case 3:
        frame_d.SetData(str_data);
        serial_interface.AsyncWriteFrame(&frame_d);
        break;
    }
    }
    else qDebug() << "Serial Interface not established. Start First";
}
*/


void XbeeInterface::startComms() {

    qDebug() << "Starting Serial Interface";
    commNode.Run();
    comms = true;
}

void XbeeInterface::stopComms() {
    qDebug() << "Stopping Serial Interface";
    commNode.Stop();
    comms = false;
}


/*
void SingletonTest::handleSignalExample(const QVariant& object) {
    //start button will pass in entire mainPage object

//    qDebug() << "Signal Passes In - " << object;
//    QQuickItem *item  = qobject_cast<QQuickItem*>(object.value<QObject*>());
//    qDebug() << item->width();

    // cast as a QObject to gain access to property read and write
    QObject *obj = object.value<QObject*>();

//    qDebug() << QQmlProperty::read(obj, "angle");
//    QQmlProperty::write(obj,"angle", 124);

    qDebug() << QQmlProperty::read(obj, "searchChunkCoords");
//    QJSValue* array = QQmlProperty::read(obj, "searchChunkCoords").value<QJSValue*>();


}
*/
