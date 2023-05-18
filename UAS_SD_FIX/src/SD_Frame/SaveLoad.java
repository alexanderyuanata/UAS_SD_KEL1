package SD_Frame;

import java.io.*;

class SaveLoad {
    private static final String FILE_NAME = "tasklist.dat";

    public static void saveTaskList(TaskList taskList) {
        try {
            FileOutputStream fileOut = new FileOutputStream(FILE_NAME);
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(taskList);
            objectOut.close();
            fileOut.close();
            System.out.println("Task list saved successfully.");
        } catch (IOException e) {
            System.out.println("Error saving task list: " + e.getMessage());
        }
    }

    public static TaskList loadTaskList() {
        TaskList taskList = null;
        try {
            FileInputStream fileIn = new FileInputStream(FILE_NAME);
            ObjectInputStream objectIn = new ObjectInputStream(fileIn);
            taskList = (TaskList) objectIn.readObject();
            objectIn.close();
            fileIn.close();
            System.out.println("Task list loaded successfully.");
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Error loading task list: " + e.getMessage());
        }
        return taskList;
    }
}


