import java.rmi.*;
import java.rmi.server.*;
import java.util.*;

public class Alien extends UnicastRemoteObject implements AlienInterface{
        static Map <String,AlienInterface> connection_pool = new HashMap();
	public String name,role;
        public int hp,status;
        public int Deputy;
	public AlienInterface client=null;
        Map <String,String> role_pool=new HashMap();
        
        public Alien(String name) throws RemoteException{
            this.name = name;
            this.hp=3;
            this.status=0;
            this.role = "Passenger";
            this.Deputy=0;
            

            
        }
        
        public String getName() throws RemoteException {
		return this.name;
	}
 
	public void setClient(AlienInterface c){
		client=c;
	}
 
	public AlienInterface getClientByName(String name){
		if (this.name.equals(name))return client;else return null;
	}
        
        public void setRole(String role){
            this.role=role;
        }
        
        public void StartGame(){
            
        }
        
        public Map ListRole(){
            return role_pool;
        }
        
        public boolean RegisterRole(String role,String m){
            if ((role_pool.containsKey(role)) && (getClientByName(m)!=null)){
                if (role_pool.get(role).equals("free")){
                    role_pool.put(role, m);
                  
                    this.setRole(role);//??? будет ли работать
                   
                    System.out.println("Добавлен "+ role+" "+name);
                    
                    return true;
                }else System.out.println("Роль "+role+" уже кем-то занята");
            }
            return false;
        }
        
        public boolean RegisterName(String name,AlienInterface m){
            if ((name!=null) && (m!=null)){
                if (connection_pool.get(name)==null){
                    connection_pool.put(name, m);
                   
                    System.out.println("Добавлен [pas]"+ name);
                    
                    return true;
                }else System.out.println("Клиент "+name+" уже зарегистрирован");
            }
            return false;
        }       
        
}
