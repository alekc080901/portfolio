package com.company;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.HashSet;

public class Restaurant {

    private final HashSet<Client> clients = new HashSet<>();

    public void addClient(Client client) {
        clients.add(client);
    }

    public void writeInfo() {

        try (FileOutputStream fos = new FileOutputStream("clients_info.bin")) {
            ObjectOutputStream ous = new ObjectOutputStream(fos);

            for (Client client : clients)
                if (client.getAge() >= 65)
                    ous.writeObject(client);
            ous.writeObject(null);
        }

        catch (IOException e) {
            System.out.println("Во время выполнения произошла ошибка " + e.toString());
            return;
        }

        System.out.println("Информация записана в файл рестораном");
    }

    public void showClientInfo() {
        clients.forEach(System.out::println);
    }

    public HashSet<Client> getClients() {
        return clients;
    }
}
