package com.company;

import java.util.ArrayList;
import java.util.HashMap;

public class Library {

    private final HashMap<LibraryVisitors, ArrayList<Book>> readersMap = new HashMap<>();
    private final ArrayList<Book> allBooks = new ArrayList<>();

    public void lendBook(LibraryVisitors reader, Book book) {
        // Проверка на наличие книги
        if (getBorrowedBooksList().contains(book)) {
            System.out.println("В данный момент эта книга отсутствует.");
            return;
        }

        readersMap.putIfAbsent(reader, new ArrayList<>());
        readersMap.get(reader).add(book);
    }

    public void takeBackBook(LibraryVisitors reader, Book book) {
        readersMap.get(reader).remove(book);
    }

    // Список взятых книг
    public ArrayList<Book> getBorrowedBooksList() {
        return new ArrayList<>(getInversedReaders().keySet());
    }

    // Список оставшихся книг
    public ArrayList<Book> getAvailableBooks() {
        ArrayList<Book> availableBooks = new ArrayList<>();
        for (Book j : allBooks)
            if (!getBorrowedBooksList().contains(j))
                availableBooks.add(j);

        return availableBooks;
    }

    public String getMaxReader() {
        ArrayList<LibraryVisitors> maxReaders = new ArrayList<>();
        StringBuilder surnames = new StringBuilder();

        // Поиск максимального количества книг
        int maxSize = -1;
        for (HashMap.Entry<LibraryVisitors, ArrayList<Book>> i : readersMap.entrySet()) {
            if (i.getValue().size() > maxSize) {
                maxSize = i.getValue().size();
                maxReaders.clear(); // Каждый раз, когда находится значение выше, список обновляется
                maxReaders.add(i.getKey());
            } else if (i.getValue().size() == maxSize)
                maxReaders.add(i.getKey());
        }

        // Преобразование списка читателей в строку фамилий
        maxReaders.forEach(reader -> surnames.append(reader.getSURNAME()).append(", "));
        if (surnames.length() != 0)
            surnames.replace(surnames.length() - 2, surnames.length() - 1, ".");

        return surnames.toString();
    }

    public String findReaderByTitleBook(String title) {
        ArrayList<LibraryVisitors> readersOfBook = new ArrayList<>();
        StringBuilder surnames = new StringBuilder();

        // Находит читателя книги по названию
        for (Book book : getBorrowedBooksList())
            if (book.getTITLE().equals(title))
                readersOfBook.addAll(getInversedReaders().get(book));

        // Преобразует список читателей в строку фамилий. Последний знак заменяется точкой
        readersOfBook.forEach(reader -> surnames.append(reader.getSURNAME()).append(", "));
        if (surnames.length() != 0)
            surnames.replace(surnames.length() - 2, surnames.length() - 1, ".");

        return surnames.toString();
    }

    // Меняет местами ключи и значения карты Читатель: Книги на Книга: Читатели
    private HashMap<Book, ArrayList<LibraryVisitors>> getInversedReaders() {

        HashMap<Book, ArrayList<LibraryVisitors>> inversed = new HashMap<>();

        for (HashMap.Entry<LibraryVisitors, ArrayList<Book>> i : readersMap.entrySet()) {
            i.getValue().forEach(book ->
            {
                inversed.putIfAbsent(book, new ArrayList<>());
                inversed.get(book).add(i.getKey());
            });
        }
        return inversed;
    }

    // Основная информация о библиотеке
    public void printInfo() {
        readersMap.forEach((reader, books) -> System.out.printf("%s:\n%s\n", reader.getSURNAME(), books));

        System.out.print("\nДоступные книги: ");
        for (Book j : getAvailableBooks())
            System.out.print(j + "; ");
    }


    public void addBook(Book b) {
        allBooks.add(b);
    }
}
