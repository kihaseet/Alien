/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Тёса
 */
import java.rmi.*;
import java.rmi.server.*;
import java.util.*;
import java.rmi.registry.*;

public class AlienClient {
    public static void main (String[] argv) {
	try {
//System.setSecurityManager(new RMISecurityManager());
            Scanner s=new Scanner(System.in);
            System.out.println("Enter Your name and press Enter:");
            String name=s.nextLine().trim();
            Registry registry = LocateRegistry.getRegistry(null, 2099);
                        //RemoteHelloService service = (RemoteHelloService) registry.lookup("HelloService");
            AlienInterface client = new Alien(name);
            
		    	AlienInterface server = (AlienInterface)registry.lookup("ABC");
                        
                      //  int n = server.register(name, client);
                        if (!server.RegisterName(name, client))
                            throw new Exception("Couldn't connect to server");
                        
		    	//String msg="["+client.getName()+"] got connected";
		    	
                        //server.send(client.getName(),msg);
		    	System.out.println("[System] Chat Remote Object is ready:");
                      //  server.setClient(client);
                        System.out.println("Выберите роль из списка досупных:");
                        Map role_list=server.ListRole();

                        Iterator i = role_list.entrySet().iterator();

                        while (i.hasNext()){
                            Map.Entry pairs = (Map.Entry)i.next();
                            if (pairs.getValue().equals("free"))
                                System.out.println(pairs.getKey());
                            i.remove();
                        }
                        String text;
		    	while(true){
                             text=s.nextLine();
                        if (server.RegisterRole(text, name)) {
                                System.out.println("Роль добавлена");
                                client.setRole(text);
                                break;
                                }
                            else System.out.println("Ошибка добавления роли");
		    	}
                        
                    while (!client.getStarted()){
                        Thread.sleep(1000);
                    }
                     
                    System.out.println("Для голосования введите имя, для подтверждения - дважды");;
                    while(true){
                    String n=s.nextLine().trim();
                        if(server.VoiceFromTo(name, n)){
                        System.out.println("Голос отдан");
                        } else System.out.println("Неправильное имя");
            
            
        }
 
	    	}catch (Exception e) {
	    		System.out.println("[System] Server failed: " + e);
	    	}
		}
}