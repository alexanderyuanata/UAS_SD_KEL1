package SD_Frame;

public class TaskList {
    private Task head;
    private Task tail;
    
    //constrcutor
    public TaskList(){
        this.head = null;
        this.tail = null;
    }
    
    public TaskList(Task head){
        this.head = head;
        this.tail = this.head;
    }
    
    //methods
    //tambah node ke list
    public void addTask(Task new_task){
        //jika belum ada head, buat baru
        if (this.head == null){
            this.head = new_task;
        }
        //jika ada, taruh di ujung
        else {
            Task current = this.head;
            while (current.getNext() != null){
                current = current.getNext();
            }
            current.setNext(new_task);
        }
        this.tail = new_task;
    }
    
    //deletes tail and set to previous node
    public void deleteTail(){
        Task current = this.head;
        while (current.getNext() != this.tail){
            current = current.getNext();
        }
        this.tail = current;
    }
    
    public void deleteHead(){
        this.head = this.head.getNext();
    }
    
    public void deleteIndex(int index){
        
    }
    
    //get
    public Task getHead(){
        return this.head;
    }
    
    public Task getTail(){
        return this.tail;
    }
}
