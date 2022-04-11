package ru.nikitin;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import ru.nikitin.services.impl.StationaryServiceImpl;
import ru.nikitin.entities.Stationery;

import java.util.Scanner;

public class Main {
    public static String inputString(boolean lower) {
        Scanner in = new Scanner(System.in);
        String text = in.nextLine();
        while (text.equals("")) {
            System.out.println("Поле не должно быть пустым!");
            text = in.nextLine();
        }
        if (lower)
            text = text.toLowerCase();
        return text;
    }

    public static int inputNat(boolean strict) {
        Scanner in = new Scanner(System.in);

        int x;
        while (true) {
            try {
                x = in.nextInt();
                in.nextLine();

                if (x < 0)
                    throw new java.util.InputMismatchException("Value is below zero!");

                if (strict && x <= 0)
                    throw new java.util.InputMismatchException("Value is below zero!");
                break;

            } catch (java.util.InputMismatchException e) {
                System.out.println("Input the correct value!");
                in.nextLine();
            }
        }
        return x;
    }

    public static Double inputDouble(double bottomBound, double upperBound) {
        Scanner in = new Scanner(System.in);

        double x;
        while (true) {
            try {
                x = in.nextDouble();
                in.nextLine();

                if (x < bottomBound || x > upperBound)
                    throw new java.util.InputMismatchException("Incorrect value!");
                break;

            } catch (java.util.InputMismatchException e) {
                System.out.println("Input the correct value!");
                in.nextLine();
            }
        }
        return x;
    }

    public static Stationery inputStationery() {

        System.out.println("Введите тип канцтовара (обязательное поле):");
        String type = inputString(true);

        System.out.println("Введите подтип канцтовара:");
        String subtype = inputString(true).toLowerCase();

        System.out.println("Введите цену товара (обязательное поле):");
        Double price = inputDouble(0, Double.POSITIVE_INFINITY);

        System.out.println("Введите количество канцтовара на складе:");
        int amount = inputNat(false);

        System.out.println("Введите производителя канцтовара:");
        String manufacturer = inputString(true).toLowerCase();

        return new Stationery(type, price, amount, subtype, manufacturer);
    }

    public static int inputId() {
        System.out.println("Введите id элемента:");
        return inputNat(false);
    }

    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(SpringConfiguration.class);
        StationaryServiceImpl service = context.getBean("stationaryServiceImpl", StationaryServiceImpl.class);

        while (true) {
            System.out.println("Введите команду:");
            System.out.println("1. Добавить новый элемент;");
            System.out.println("2. Вывести содержимое БД;");
            System.out.println("3. Редактировать элемент;");
            System.out.println("4. Удалить элемент;");
            System.out.println("5. Поиск продукции определенного производителя;");
            System.out.println("6. Завершение работы приложения.");

            int choice = inputNat(true);
            switch (UserMenu.values()[choice - 1]) {
                case ADD -> {
                    Stationery stationery = inputStationery();
                    service.add(stationery);
                    System.out.println("Элемент успешно добавлен.");
                }

                case OUTPUT -> {
                    service.getAll().forEach(System.out::println);
                }

                case UPDATE -> {
                    int id = inputId();
                    Stationery stationery = inputStationery();
                    if (service.update(id, stationery))
                        System.out.println("Элемент успешно удален.");
                    else
                        System.out.println("Элемента с таким id нет!");
                }

                case REMOVE -> {
                    int id = inputId();
                    if (service.delete(id))
                        System.out.println("Элемент успешно удален.");
                    else
                        System.out.println("Элемента с таким id нет!");
                }

                case FIND_MANUFACTURER -> {
                    System.out.println("Введите производителя:");
                    String manufacturer = inputString(true);
                    System.out.println(service.getByManufacturer(manufacturer));
                }

                case EXIT -> {
                    context.close();
                    System.exit(1);
                }

                default -> {
                    System.out.println("Введите значение от 1 до 6!");
                }
            }
        }
    }
}
