package ru.nikitin.client;

import ru.nikitin.server.entities.Stationery;

import java.net.MalformedURLException;
import java.net.URL;

public class Main {

    public static void main(String[] args) {

        try {
            URL url = new URL("http://localhost:8080/");
        } catch (MalformedURLException e) {
            System.out.println("Failing to establish a connection!");
            return;
        }

        while (true) {
            System.out.println("Введите команду:");
            System.out.println("1. Добавить новый элемент;");
            System.out.println("2. Вывести содержимое БД;");
            System.out.println("3. Редактировать элемент;");
            System.out.println("4. Удалить элемент;");
            System.out.println("5. Поиск продукции определенного производителя;");
            System.out.println("6. Завершение работы приложения.");

            int choice = InputHandler.inputNat(true);
            switch (UserMenu.values()[choice - 1]) {
                case ADD -> {
                    Stationery stationery = InputHandler.inputStationery();
                    Requests.postStationery("http://localhost:8080/json/stationery/table", stationery);
                    System.out.println("Element has been successfully added!");
                }

                case OUTPUT -> {
                    Stationery[] response = Requests.getStationeryTable("http://localhost:8080/json/stationery/table");

                    for (Stationery stationery: response) {
                        System.out.println(stationery);
                    }

                }

                case UPDATE -> {
                    int id = InputHandler.inputId();
                    Stationery stationery = InputHandler.inputStationery();
                    Requests.updateStationery(
                            "http://localhost:8080/json/stationery/table/" + id,
                            stationery
                    );

                    System.out.println("Element has been successfully updated!");
                }

                case REMOVE -> {
                    int id = InputHandler.inputId();

                    Requests.deleteStationery(
                            "http://localhost:8080/json/stationery/table/" + id,
                            id
                    );

                    System.out.println("Element has been successfully deleted!");
                }

                case SEARCH -> {
                    System.out.println("Введите производителя:");
                    String manufacturer = InputHandler.inputString(true);

                    Stationery[] response = Requests.getStationeryTable(
                            "http://localhost:8080/json/stationery/table/" + manufacturer
                    );

                    for (Stationery stationery: response) {
                        System.out.println(stationery);
                    }
                }

                case EXIT -> {
                    System.exit(1);
                }

                default -> {
                    System.out.println("Введите значение от 1 до 6!");
                }
            }
        }
    }
}
