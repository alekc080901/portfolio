package com.company;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Scanner;

public class Main {

    public static int inputNat() {
        Scanner in = new Scanner(System.in);

        int x;
        while (true) {
            try {
                x = in.nextInt();
                in.nextLine();

                if (x < 0)
                    throw new java.util.InputMismatchException("Value is below zero");
                break;

            } catch (java.util.InputMismatchException e) {
                System.out.println("Input the correct value");
                in.nextLine();
            }
        }
        return x;
    }

    public static double inputDouble(double bottomBound, double upperBound) {
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

    public static String inputString() {
        Scanner in = new Scanner(System.in);
        return in.nextLine();
    }

    public static Product chooseProduct() {
        while (true) {
            System.out.println("Введите тип канцтовара (обязательное поле):");
            String price = inputString();

            System.out.println("Введите жирность продукта (в процентах):");
            double fatContent = inputDouble(Double.NEGATIVE_INFINITY, 99.9);

            return new MilkProduct(productName, price, fatContent);
        }
    }

    public static int inputIndex(Collection<Product> array) {
        int index;
        while (true) {
            index = inputNat();
            if (index < array.size() && index >= 0)
                break;
            System.out.println("Введите корректный индекс!");
        }
        return index;
    }

    public static void main(String[] args) {
        ShoppingCart shoppingCart = new ShoppingCart();
        while (true) {
            System.out.println("Введите команду:");
            System.out.println("1. Добавить новый элемент;");
            System.out.println("2. Вывести содержимое БД;");
            System.out.println("3. Редактировать элемент;");
            System.out.println("4. Удалить элемент;");
            System.out.println("5. Поиск продукции определенного производителя;");
            System.out.println("6. Завершение работы приложения.");

            int choice = inputNat();
            switch (UserMenu.values()[choice - 1]) {
                case ADD -> {

                }

                case REMOVE -> {
                    Product product = chooseProduct();
                    shoppingCart.removeProduct(product);
                    System.out.println("Элемент удален");
                }

                case OUTPUT -> {
                    if (shoppingCart.getProducts().size() == 0) {
                        System.out.println("Корзина пуста.");
                        break;
                    }

                    System.out.println("-------------------------------------");
                    for (Product prod : shoppingCart.getProducts()) {
                        System.out.println(prod);
                        System.out.println("-------------------------------------");
                    }
                    System.out.println("-------------------------------------");
                    System.out.println("Итоговая цена: " + shoppingCart.getTotalPrice());

                }

                case EXIT -> {
                    System.exit(1);
                }

                default -> {
                    System.out.println("Введите значение от 1 до 5!");
                }
            }
        }
    }
}
