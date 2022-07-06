package ru.niatomi.model.domain.arduinoConfig;

import lombok.AllArgsConstructor;
import lombok.Data;
import org.springframework.data.mongodb.core.mapping.Document;

import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

/**
 * @author niatomi
 */
@Document
@Data
@AllArgsConstructor
public class UpdatableConfig {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private boolean referenceIsUpdatable;
    private boolean isTimeIsUpdatable;

}
