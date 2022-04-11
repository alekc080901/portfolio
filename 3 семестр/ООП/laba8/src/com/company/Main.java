package com.company;

public class Main {

    public static void main(String[] args) {

        Restaurant restaurant = new Restaurant();

	    Client client1 = new Client("Александр", 80);
        Client client2 = new Client("Михаил", 30);
        Client client3 = new Client("Аркадий", 15);
        Client client4 = new Client("Евгения", 72);
        Client client5 = new Client("Ксения", 57);
        Client client6 = new Client("Геннадий", 66);

        client1.eat(restaurant, 1500);
        client1.eat(restaurant, 3000);
        client2.eat(restaurant, 560);
        client3.eat(restaurant, 2300);
        client4.eat(restaurant, 1800);
        client4.eat(restaurant, 1200);
        client5.eat(restaurant, 3200);
        client6.eat(restaurant, 1670);

        restaurant.showClientInfo();
        System.out.println();

        restaurant.writeInfo();
        Rosstat.readInfo();
        System.out.println();

        Rosstat.showReceivedInfo();

        System.out.println("\nСредняя сумма чеков:");
        System.out.println(Rosstat.meanCalculate());

    }
}
