package com.company;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.List;

public class Rosstat {

    private static final List<Client> clientsInfo = new ArrayList<>();

    public static void readInfo() {
        try (FileInputStream fis = new FileInputStream("clients_info.bin")) {
            ObjectInputStream ois = new ObjectInputStream(fis);

            Client client;
            while ((client = (Client) ois.readObject()) != null) {
                clientsInfo.add(client);
            }

            System.out.println("Информация считана из файла Росстатом");
        }

        catch (IOException e) {
            System.out.println("Произошла ошибка при чтении");
            System.out.println(e.toString());
        }

        catch (ClassNotFoundException e) {
            System.out.println("Класс не найден");
        }
    }

    public static void showReceivedInfo() {
        clientsInfo.forEach(System.out::print);
    }

    public static long meanCalculate() {
        double sum = 0;
        for (Client client : clientsInfo)
            sum += client.getReceiptsSum();

        return Math.round(sum / clientsInfo.size());
    }
}
