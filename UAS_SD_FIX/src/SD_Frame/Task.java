package SD_Frame;

import java.io.Serializable;

public class Task implements Serializable {
    
    private String title = "";
    private String text = "";
    private boolean done = false;
    
    private Task next = null;
    
    //constructor
    public Task(){
        
    }
    
    public Task(String title, String text){
        this.title = title;
        this.text = text;
    }
    
    public Task(String title, String text, boolean done){
        this.title = title;
        this.text = text;
        this.done = done;
    }
    
    public Task(String title, String text, Task next){
        this.title = title;
        this.text = text;
        this.next = next;
    }
    
    
    //methods
    
    public void displayData(){
        System.out.println("title: " + this.title + ", done: " + this.done + ", desc: " + this.text);
    }
    
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
    
    public boolean getDone(){
        return this.done;
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
