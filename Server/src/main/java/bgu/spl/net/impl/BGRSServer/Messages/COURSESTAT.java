package bgu.spl.net.impl.BGRSServer.Messages;

import bgu.spl.net.impl.BGRSServer.CourseStat;
import bgu.spl.net.impl.BGRSServer.Database;

public class COURSESTAT implements Message<Database> {
    private final short opcode =7;
    private short courseNum;
    private String nameOfAdmin;
    public COURSESTAT(short courseNum){
        this.courseNum = courseNum;
    }
    @Override
    public Message execute(Database arg) {
        CourseStat data = arg.getCourseState(courseNum,nameOfAdmin);
        if(data == null)
            return new ERR(opcode);
        String attachment = "Course: ("+courseNum+") " + data.getCourseName() + "\nSeats Available: "+ (data.getNumOfMaxStudents()-data.getNumOfRegistered())+"/"+ data.getNumOfMaxStudents() + "\nStudents Registered: ";
        String registered = "[";
        for(int i=0;i<data.getRegisteredStudents().size();i++){
            registered += data.getRegisteredStudents().get(i) + ",";
        }
        if(data.getRegisteredStudents().size() > 0) //  if we even added ,
            registered = registered.substring(0,registered.length()-1); // remove the last , char
        registered += "]";
        attachment += registered;
        return new ACK(opcode,attachment);
    }

    @Override
    public short getOpCode() {
        return opcode;
    }

    @Override
    public void AddUserName(String userName) {
        nameOfAdmin = userName;
    }

}
