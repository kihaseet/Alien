import java.rmi.*;
import java.rmi.server.*;
import java.util.*;

public class Alien extends UnicastRemoteObject implements AlienInterface {

    static Map<String, AlienInterface> connection_pool = new HashMap();
    public String name, role;
    public int hp,maxhp, status;
    public int Deputy;
    public AlienInterface client = null;
    public boolean isStarted=false;
    
    Map<String, String> role_pool = new HashMap();
    List<Tool> Inventory;

    public Alien(String name) throws RemoteException {
        this.name = name;
        this.hp = 3;
        this.maxhp=3;
        this.status = 0;
        this.role = "Passenger";
        this.Deputy = 0;
        this.Inventory = new ArrayList();
        this.isStarted=false;

    }
    

    @Override
    public void setTool(String name){
        this.Inventory.add(new Tool(name));
    }
    
    public void useTools(AlienInterface j, Tool t){
        
    }

    public String getName() throws RemoteException {
        return this.name;
    }

    public void setClient(AlienInterface c) {
        client = c;
    }

    public AlienInterface getClientByName(String name) {
        if (this.name.equals(name)) {
            return client;
        } else {
            return null;
        }
    }

    public void setRole(String role) {
        this.role = role;
    }

    public void StartGame() {
        System.out.println("Let's play!");
        this.isStarted=true;

    }
    
    @Override
    public boolean getStarted(){
        return this.isStarted;
    }

    public Map ListRole() {
        return role_pool;
    }

    public boolean RegisterRole(String role, String m) {
        if ((role_pool.containsKey(role)) && (getClientByName(m) != null)) {
            if (role_pool.get(role).equals("free")) {
                role_pool.put(role, m);

                this.setRole(role);//??? будет ли работать

                System.out.println("Добавлен " + role + " " + name);

                return true;
            } else {
                System.out.println("Роль " + role + " уже кем-то занята");
            }
        }
        return false;
    }

    public boolean RegisterName(String name, AlienInterface m) {
        if ((name != null) && (m != null)) {
            if (connection_pool.get(name) == null) {
                connection_pool.put(name, m);

                System.out.println("Добавлен [pas]" + name);

                return true;
            } else {
                System.out.println("Клиент " + name + " уже зарегистрирован");
            }
        }
        return false;
    }

    public void print(String msg) {
        System.out.println(msg);
    }
    
   
    public void setHP(int heal)throws RemoteException{
        this.hp=this.hp+heal;
        if (this.hp>maxhp)this.hp=maxhp;
        //if (this.hp<0) убить персонажа
    }
            
    public int getHP()throws RemoteException{
            return this.hp;
        }
    
     public Map Vote(Map <AlienInterface, HashMap<AlienInterface,Integer>> votelist) throws RemoteException{
        for (AlienInterface key : votelist.keySet())
        {
            HashMap<AlienInterface, Integer> boxHolder = votelist.get(key);
            for (AlienInterface innerKey : boxHolder.keySet())
            {
                System.out.println(key.getName()+"=>"+innerKey.getName()+" "+boxHolder.get(innerKey));
            }
        }
        return null; 
    }
     
   public boolean VoiceFromTo(String from, String to){
       return true;
   }
}
