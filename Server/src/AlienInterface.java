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
import java.util.*;

public interface AlienInterface extends Remote{
    public boolean RegisterName(String name,AlienInterface m) throws RemoteException;
    public boolean RegisterRole(String role,String m) throws RemoteException;
    public Map ListRole() throws RemoteException;
    public void StartGame() throws RemoteException;
    public String getName() throws RemoteException;
    public boolean getStarted()throws RemoteException;;
    public void setRole(String role) throws RemoteException;
    public void setClient(AlienInterface c)throws RemoteException;
    public AlienInterface getClientByName(String name) throws RemoteException;
    public void setTool(String name) throws RemoteException;
    public void setHP(int heal) throws RemoteException;
    public void print(String msg) throws RemoteException;
    public int getHP()throws RemoteException;
    public void useTools(AlienInterface j, Tool t) throws RemoteException;
    public Map Vote (Map <AlienInterface, HashMap<AlienInterface,Integer>> votelist) throws RemoteException;
    public boolean VoiceFromTo(String from, String to) throws RemoteException;
}
