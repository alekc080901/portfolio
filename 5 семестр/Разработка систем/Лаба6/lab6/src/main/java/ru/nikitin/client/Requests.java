package ru.nikitin.client;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicHeader;
import org.springframework.web.client.RestTemplate;
import ru.nikitin.server.entities.Stationery;

import java.net.http.HttpClient;
import java.util.Optional;

public class Requests {
    private static final RestTemplate restTemplate = new RestTemplate();

    public static Stationery[] getStationeryTable(String targetURL) {
        return restTemplate.getForObject(targetURL, Stationery[].class);
    }

    public static void postStationery(String targetURL, Stationery stationery) {
        restTemplate.postForObject(targetURL, stationery, Stationery.class);
    }

    public static void updateStationery(String targetURL, Stationery stationery) {
        restTemplate.put(targetURL, stationery, stationery.getId());
    }

    public static void deleteStationery(String targetURL, int id) {
        restTemplate.delete(targetURL, id);
    }
}
