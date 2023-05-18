package SD_Frame;

public class Task {
    
    private String title = "";
    private String text = "";
    private String date = "";
    private String time = "";
    private boolean done = false;
    
    private Task next = null;
    
    //constructor
    public Task(String title, String text, String date, String time){
        this.title = title;
        this.text = text;
        this.date = date;
        this.time = time;
    }
    
    public Task(String title, String text, String date, String time, Task next){
        this.title = title;
        this.text = text;
        this.date = date;
        this.time = time;
        this.next = next;
    }
    
    
    //methods
    
    
    //get
    public Task getNext(){
        return this.next;
    }
    
    public String getTitle(){
        return this.title;
    }
    
    public String getText(){
        return this.text;
    }
    
    //set
    public void setNext(Task next){
        this.next = next;
    }
    
    public void setTitle(String title){
        this.title = title;
    }
    
    public void setText(String text){
        this.text = text;
    }
    
    public void setDone(boolean done){
        this.done = done;
    }
}
