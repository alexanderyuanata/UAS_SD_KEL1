    package SD_Frame;

import java.io.Serializable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;

public class TaskList implements Serializable {

    private Task head;
    private Task tail;
    private int members = 0;
    
    //constructor
    public TaskList() {
        this.head = null;
        this.tail = null;
    }

    public TaskList(Task head) {
        this.head = head;
        this.tail = this.head;
        members++;
    }

    //methods
    //tambah node ke list di tail
    public void addTask(Task new_task) {
        //jika belum ada head, buat baru
        if (this.head == null) {
            this.head = new_task;
        } //jika ada, taruh di ujung
        else {
            Task current = this.head;
            while (current.getNext() != null) {
                current = current.getNext();
            }
            current.setNext(new_task);
        }
        this.tail = new_task;
        members++;
    }
    
    //tambah node di index list (1-n)
    public void insertTask(Task new_task, int index) {
        //jika disisipkan di head
        if (index == 1){
            new_task.setNext(this.head);
            this.head = new_task;
        }
        //jika disisipkan di tail
        else if (index == members){
            Task prev = this.head;
            while(prev.getNext() != this.tail){
                prev = prev.getNext();
            }
            prev.setNext(new_task);
            new_task.setNext(this.tail);
        }
        else {
            Task prev = null;
            Task current = this.head;

            //pergi ke index
            for (int i = 1; i < index; i++) {
                prev = current;
                current = current.getNext();
                //jika luar list indeksnya
                if (current == null) {
                    System.out.println("INDEX OUT OF BOUNDS");
                    return;
                }
            }
            
            //sisipkan pada index ini
            prev.setNext(new_task);
            new_task.setNext(current);
        }
        members++;
    }

    
    //deletes a task
    public void deleteTask(Task selected){
        if (selected == this.head){
            this.head = this.head.getNext();
            members--;
            return;
        }
        Task current = this.head;
        
        if (selected == this.tail){
            while (current.getNext() != this.tail) {
                current = current.getNext();
            }
            this.tail = current;
            members--;
        }
        
        Task prev = null;
        
        while (current != null){
            if (current == selected){
                prev.setNext(current.getNext());
                members--;
            }
            prev = current;
            current = current.getNext();
        }
    }
    
    
    //deletes tail and set to previous node
    public void deleteTail() {
        if (this.tail == this.head){
            this.head = null;
            this.tail = null;
            return;
        }
        
        Task current = this.head;
        while (current.getNext() != this.tail) {
            current = current.getNext();
        }
        this.tail = current;
        members--;
    }
    
    //hapus head
    public void deleteHead() {
        this.head = this.head.getNext();
        members--;
    }

    //index starts from 1(head) to n(tail)
    public void deleteIndex(int index) {
        Task prev = null;
        Task current = this.head;

        //pergi ke index
        for (int i = 1; i < index; i++) {
            prev = current;
            current = current.getNext();
            //jika luar list indeksnya
            if (current == null) {
                System.out.println("INDEX OUT OF BOUNDS");
                return;
            }
        }
        //hapus current
        prev.setNext(current.getNext());
        members--;
    }    
    
    
    public TableModel createTableModel() {
        String[] columnNames = {"Title", "Done"};
        DefaultTableModel model = new DefaultTableModel(columnNames, 0);

        Task current = head;
        while (current != null) {
            Object[] rowData = {current.getTitle(), current.getDone()};
            model.addRow(rowData);
            current = current.getNext();
        }

        return model;
    }
    
    //get
    //ambil head
    public Task getHead() {
        return this.head;
    }
    
    //ambil tail
    public Task getTail() {
        return this.tail;
    }
    
    //ambil node di index
    public Task getIndex(int index){
        Task current = this.head;
        for (int i = 1; i < index; i++) {
            current = current.getNext();
        }
        return current;
    }
}
