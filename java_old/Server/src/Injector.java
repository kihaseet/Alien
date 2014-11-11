
import java.rmi.RemoteException;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Тёса
 */
public class Injector extends Tool{

    @Override
    public void UseTool(AlienInterface j) {
        try {
            j.setHP(2);
            this.counter=2;
        } catch (RemoteException ex) {
            Logger.getLogger(Injector.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public Injector(){
    }


    public void UltaUseTool(AlienInterface j) {
    }
    
    
}
