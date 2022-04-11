package ru.nikitin.receivers;

import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import ru.nikitin.handlers.EmailHandler;
import ru.nikitin.model.Message;
import ru.nikitin.model.Stationery;

@Component
public class Receiver {
    @Autowired
    private EmailHandler emailHandler;

    private final String ADMIN_EMAIL = "rei.nikitin@ya.ru";
    private final String SUBJECT = "Новая покупа";

    @RabbitListener(queues = "stationery-queue", containerFactory =
            "rabbitListenerContainerFactory")
    public void listen(Message message) {
        Stationery stationery = message.getStationery();
        String messageText =
                "Stationery " + stationery.getType() +
                ", " + stationery.getSubtype() +
                " (id " + stationery.getId() +
                ") by \"" + stationery.getManufacturer() + "\" has been bought.";

        emailHandler.sendEmail(ADMIN_EMAIL, SUBJECT, messageText);
    }
}
