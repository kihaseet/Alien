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
import java.rmi.registry.*;
import java.util.*;

public class AlienServer {
public static void main (String[] argv) {
    try {

	    	Scanner s=new Scanner(System.in);
	    	System.out.println("Enter Your name and press Enter:");
	    	String name=s.nextLine().trim();
 

                final Registry registry = LocateRegistry.createRegistry(2099);
 	    	Alien server = new Alien(name);
	    	registry.rebind("ABC", server);
	    	System.out.println("[System] Chat Remote Object is ready:");

                String text;
	    	while(true){
                    text=s.nextLine().trim();
                    if(text.equals("Start")) 
                        server.StartGame();
                    while (server.DayTime()){
                        server.NightTime();
                    }
                    
	    	}
 
    	}catch (Exception e) {
    		System.out.println("[System] Server failed: " + e);
    	}
	}
}
