package bgu.spl.net.impl.BGRSServer.Messages;

import bgu.spl.net.impl.BGRSServer.Database;

public class LOGOUT implements Message<Database> {
    private final short opcode =4;
    private String userName;
    @Override
    public Message execute(Database arg) {
        if(arg.Logout(userName))
            return new ACK(opcode,"");
        return new ERR(opcode);
    }

    @Override
    public short getOpCode() {
        return opcode;
    }

    @Override
    public void AddUserName(String userName) {
        this.userName = userName;
    }
}
