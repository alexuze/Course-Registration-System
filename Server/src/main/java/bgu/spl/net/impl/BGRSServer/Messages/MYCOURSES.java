package bgu.spl.net.impl.BGRSServer.Messages;

import bgu.spl.net.impl.BGRSServer.Database;

import java.util.List;

public class MYCOURSES implements Message<Database> {
    private final short opcode =11;
    private String userName;
    @Override
    public Message execute(Database arg) {
        // TODO : need to create an ACK or ERR message and create the string that represents the courses
        List<Integer> coursesList =  arg.getRegisteredCourses(userName);
        if(coursesList == null)
            return new ERR(opcode);
        String courses = "[";
        for(int i=0;i<coursesList.size();i++){
            courses += coursesList.get(i) + ",";
        }
        if(coursesList.size() > 0)//  if we even added ,
            courses = courses.substring(0,courses.length()-1); // remove the last , char
        courses += "]";
        return new ACK(opcode,courses);
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
