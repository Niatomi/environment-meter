package ru.niatomi.model.domain.arduinoConfig;

import lombok.*;
import org.hibernate.validator.constraints.UniqueElements;
import org.springframework.data.mongodb.core.index.Indexed;
import org.springframework.data.mongodb.core.mapping.Document;

import javax.persistence.*;
import java.time.ZonedDateTime;

/**
 * @author niatomi
 */
@Data
@Document
public class ReferenceData {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private Integer c02;

    private Double normalPh;

    private Double volume;

    private boolean isUpdated;

}
