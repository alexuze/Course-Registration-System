package bgu.spl.net.impl.BGRSServer.Messages;

import bgu.spl.net.impl.BGRSServer.Database;

public class STUDENTREG implements Message<Database> {
    private final short opcode =2;
    private String userName;
    private String password;
    public STUDENTREG(String userName,String password){
        this.userName = userName;
        this.password = password;
    }
    @Override
    public synchronized Message execute(Database arg) {
        //return arg.studentRegister(userName,password);

        if(arg.studentRegister(userName,password))
            return new ACK(opcode,"");
        return new ERR(opcode);
    }

    @Override
    public short getOpCode() {
        return opcode;
    }
}
