////
//// Created by Daniel Eisenberg on 12/01/2020.
////
//
//#include <ostream>
//#include "MyTestClientHandler.h"
//void MyTestClientHandler::handleClient(std::istream InputStream, std::ostream OutputStream) {
//    string result;
//    string line = InputStream.getline();
//
//    if (line == "end")
//        return false; ////FINISH CONNECTION!
//
//    if (cm.exist(line)) {
//        result = cm.get(line)
//    } else {
//        result = solver.solve(line);
//    }
//
//    OutputStream.write(result); ////MUST SEND RESULT TO CLIENT BEFORE FINISH - ELSE CLIENT WONT WRITE AGAIN
//    //// Use 'flush'
//
//}