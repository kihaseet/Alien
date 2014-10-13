import java.rmi.*;
import java.rmi.server.*;
import java.util.*;

public class Alien extends UnicastRemoteObject implements AlienInterface{
        static Map <String,AlienInterface> connection_pool = new HashMap();
	public String name,role;
        public int hp,status;
        public int Deputy;
	public AlienInterface client=null;
        Map <String,String> role_pool;
        
        public Alien(String name) throws RemoteException{
            this.name = name;
            this.hp=3;
            this.status=0;
            this.Deputy=0;
            this.role = "Passenger";
            role_pool = new HashMap();
            role_pool.put("Captain","free");
            role_pool.put("Senior Assistant","free");
            role_pool.put("Engineer","free");
            role_pool.put("Power Engineer","free");
            role_pool.put("Gunmen","free");
            role_pool.put("Scientist","free");
            role_pool.put("Doctor","free");
            role_pool.put("Signalmen","free");
            role_pool.put("Passenger","free");
            
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
            if (role_pool.containsKey(role)){
                if (role_pool.get(role).equals("free")){
                    if (role.equals("Passenger"))
                        role_pool.put(m, role);
                    else role_pool.put(role, m);
                    System.out.println("Добавлен "+ role+" "+m);
                   // if((!role.equals("Captain")) && (!role.equals("Senior Assistant")) && (!role.equals("Passenger")))
                  //      if(!role.contains("Deputy"))
                  //          role_pool.put("Deputy of "+role, "free");
                    if ((!role_pool.get("Captain").equals("free")) &&
                         !role_pool.get("Senior Assistant").equals("free") &&
                         !role_pool.get("Engineer").equals("free") &&
                         !role_pool.get("Power Engineer").equals("free") &&
                         !role_pool.get("Gunmen").equals("free") &&
                         !role_pool.get("Scientist").equals("free") &&
                         !role_pool.get("Doctor").equals("free") &&
                         !role_pool.get("Signalmen").equals("free") &&
                         !role_pool.containsKey("Deputy of Gunmen")) {
                        role_pool.put("Deputy of Engineer","free");
                        role_pool.put("Deputy of Power Engineer","free");
                        role_pool.put("Deputy of Gunmen","free");
                        role_pool.put("Deputy of Scientist","free");
                        role_pool.put("Deputy of Doctor","free");
                        role_pool.put("Deputy of Signalmen","free");
                    }
                    
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
