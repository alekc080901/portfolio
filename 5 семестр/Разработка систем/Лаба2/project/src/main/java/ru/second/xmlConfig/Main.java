package ru.second.xmlConfig;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Main {

    public static void main(String[] args) {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext(
                "applicationContext.xml"
        );

        Backpack backpack =  context.getBean("backpack", Backpack.class);
        System.out.println(backpack.getBrandName());
        backpack.getBurden().showInfo();

        context.close();
    }
}
