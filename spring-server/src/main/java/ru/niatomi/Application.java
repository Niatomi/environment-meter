package ru.niatomi;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.repository.ReferenceDataRepository;

/**
 * @author niatomi
 */
@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Bean
    CommandLineRunner runner(ReferenceDataRepository referenceDataRepository) {
        return args -> {
            ReferenceData referenceData = new ReferenceData();
            referenceData.setId(1);
            referenceData.setVolume(5.5);
            referenceData.setNormalPh(5.5);
            referenceData.setC02(1500);
            referenceData.setUpdated(false);
            referenceDataRepository.save(referenceData);

        };

    }
}
