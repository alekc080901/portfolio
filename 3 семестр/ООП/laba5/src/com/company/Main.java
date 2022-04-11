package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);

        // ОБЪЯВЛЕНИЕ ЭКЗЕМПЛЯРОВ КЛАССОВ
        Library lib = new Library();

        Book book1 = new Book("Преступление и наказание", "Федор Достоевский", lib);
        Book book2 = new Book("Горе от ума", "Александр Грибоедов", lib);
        Book book3 = new Book("Детство", "Лев Толстой", lib);
        Book book4 = new Book("Детство", "Максим Горький", lib);
        Book book5 = new Book("Гроза", "Александр Островский", lib);
        Book book6 = new Book("Евгений Онегин", "Александр Пушкин", lib);

        Student stud1 = new Student("Макаров", book1);
        Student stud2 = new Student("Кириллов", book4);
        Student stud3 = new Student("Смирнова", book3);

        Teacher teach1 = new Teacher("Королев", book2);

        lib.printInfo();
        System.out.println("\nНажмите Enter, чтобы продолжить...\n");
        input.nextLine();

        // ВЗАИМОДЕЙСТВИЯ С КНИГАМИ
        teach1.borrowBook(book5);
        stud3.borrowBook(book5);
        stud1.returnBook(book1);
        lib.printInfo();

        System.out.println("\nНажмите Enter, чтобы продолжить...\n");
        input.nextLine();

        // printBooks()
        stud2.printBooks();
        teach1.printBooks();

        System.out.println("\nНажмите Enter, чтобы продолжить...\n");
        input.nextLine();

        // МЕТОДЫ КЛАССА LIBRARY
        System.out.println("Наибольшее количество взятых книг:\n" + lib.getMaxReader());
        System.out.println("Данную книгу взял " + lib.findReaderByTitleBook("Детство"));

        System.out.println("\nНажмите Enter, чтобы продолжить...\n");
        input.nextLine();
    }
}
