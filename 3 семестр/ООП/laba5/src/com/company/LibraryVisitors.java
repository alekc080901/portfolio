package com.company;

import java.util.ArrayList;

public abstract class LibraryVisitors {

    private final String SURNAME;
    private final ArrayList<Book> books = new ArrayList<>();

    public LibraryVisitors(String surname, Book firstBook) {
        this.SURNAME = surname;
        borrowBook(firstBook);
    }

    public abstract void printBooks();

    public void borrowBook(Book book) {
        books.add(book); // Добавляет книгу в список читателя
        book.getLIBRARY().lendBook(this, book); // Добавляет книгу в список библиотеки
    }

    public void returnBook(Book book) {
        if (books.contains(book)) {
            books.remove(book); // Удаляет книгу из списка читателя
            book.getLIBRARY().takeBackBook(this, book); // Удаляет книгу из списка библиотеки
            System.out.printf("Книга \"%s\" сдана в библиотеку.\n", book.getTITLE());
        }
        else
            System.out.printf("Книга \"%s\" не была в списке.\n", book.getTITLE());
    }

    public String getSURNAME() {
        return SURNAME;
    }

    public ArrayList<Book> getBooks() {
        return books;
    }
}
