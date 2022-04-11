package ru.second.annotationConfig;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Main {

    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(SpringConfiguration.class);

        System.out.println();

        Backpack backpack =  context.getBean("backpack", Backpack.class);
        System.out.println(backpack.getBrandName());

        System.out.println("Информация о содержимом рюкзака.");
        backpack.getBurden().showInfo();

        System.out.println();
        context.close();
    }
}
