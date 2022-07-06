package ru.niatomi;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.Bean;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.domain.arduinoConfig.UpdatableConfig;
import ru.niatomi.repository.ReferenceDataRepository;
import ru.niatomi.repository.UpdatableConfigRepository;

/**
 * @author niatomi
 */
@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Bean
    CommandLineRunner runner(ReferenceDataRepository referenceDataRepository,
                             UpdatableConfigRepository updatableConfigRepository) {
        return args -> {
            ReferenceData referenceData = new ReferenceData();
            referenceData.setId(1);
            referenceData.setVolume(5.5);
            referenceData.setNormalPh(5.5);
            referenceData.setC02(1500);
            referenceDataRepository.save(referenceData);

            updatableConfigRepository.save(new UpdatableConfig(1, true, true));

        };

    }
}
