package bgu.spl.net.impl.BGRSServer.Messages;

import bgu.spl.net.impl.BGRSServer.Database;

public class LOGIN implements Message<Database> {
    private final short opcode =3;
    private String userName;
    private String password;
    public LOGIN(String userName,String password){
        this.userName = userName;
        this.password = password;
    }
    @Override
    public Message execute(Database arg) {
        //return arg.Login(userName,password);
        if(arg.Login(userName,password))
            return new ACK(opcode,"");
        return new ERR(opcode);
    }

    @Override
    public short getOpCode() {
        return opcode;
    }
    public String getUserName(){
        return userName;
    }
}
