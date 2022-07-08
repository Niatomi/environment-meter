package ru.niatomi.mapper;

import org.mapstruct.Mapper;
import org.mapstruct.ReportingPolicy;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.dto.configFiles.ReferenceDataDto;

/**
 * @author niatomi
 */
@Mapper(
        componentModel = "spring",
        unmappedTargetPolicy = ReportingPolicy.IGNORE
)
public interface ReferenceDataMapper {

    ReferenceDataDto map(ReferenceData referenceData);
    ReferenceData map(ReferenceDataDto referenceData);

}
