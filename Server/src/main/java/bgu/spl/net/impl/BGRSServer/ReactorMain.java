package bgu.spl.net.impl.BGRSServer;
import bgu.spl.net.srv.Server;

public class ReactorMain {
    public static void main(String[] args) {
        Database database = Database.getInstance();
        Integer port = Integer.parseInt(args[0]);
        Integer threadNuber = Integer.parseInt(args[1]);
        Server.reactor(
                threadNuber,
                port, //port
                () ->  new BGRSProtocol<>(database), //protocol factory
                () -> new BGRSMessageEncoderDecoder() //message encoder decoder factory
        ).serve();
    }
}
