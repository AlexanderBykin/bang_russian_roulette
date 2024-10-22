// license-header java merge-point
//
// Attention: Generated code! Do not modify by hand!
// Generated by: TypeSafeEnumeration.vsl in andromda-java-cartridge.
// Model Class:  AndroMDAModel::net.orionlab.brr::domain::PistolType
// Metafacade:   org.andromda.metafacades.uml.Enumeration
// Stereotype:  Enumeration
//
package net.orionlab.brr.domain;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * 
 */
public enum PistolType
{
    /** TODO: Model Documentation for Enumeration Literal PISTOL1 value "PISTOL1" */
    PISTOL1("PISTOL1"),
    /** TODO: Model Documentation for Enumeration Literal PISTOL2 value "PISTOL2" */
    PISTOL2("PISTOL2");

    /**
     * The serial version UID of this class. Needed for serialization.
     */
    private static final long serialVersionUID = -2284006370158455026L;

    private final String enumValue;

    /**
     * The constructor with enumeration literal value allowing
     * super classes to access it.
     */
    private PistolType(String value)
    {
        this.enumValue = value;
    }

    /*
     * Do not override this method directly. Use an alternate name
     * if providing a different toString implementation
     * @see Object#toString()
    @Override
    public String toString()
    {
        return String.valueOf(this.enumValue);
    }
     */

    /**
     * Retrieves an instance of PistolType from <code>its name</code>.
     *
     * @param name the name to create the PistolType from.
     * @return The enumeration literal named after the 'name' argument
     */
    public static PistolType fromString(String name)
    {
        return PistolType.valueOf(name);
    }

    /**
     * Returns an enumeration literal String <code>value</code>.
     * Required by JAXB2 enumeration implementation
     *
     * @return String with corresponding value
     */
    public String value()
    {
        return this.enumValue;
    }

    /**
     * Returns an instance of PistolType from String <code>value</code>.
     * Required by JAXB2 enumeration implementation
     *
     * @param value the value to create the PistolType from.
     * @return static Enumeration with corresponding value
     */
    public static PistolType fromValue(String value)
    {
        for (PistolType enumName: PistolType.values())
        {
            if (enumName.getValue().equals(value))
            {
                return enumName;
            }
        }
        throw new IllegalArgumentException("PistolType.fromValue(" + value + ')');
    }

    /**
     * Gets the underlying value of this type safe enumeration.
     * This method is necessary to comply with DaoBase implementation.
     * @return The name of this literal.
     */
    public String getValue()
    {
        return this.enumValue;
    }

    /**
     * Returns an unmodifiable list containing the literals that are known by this enumeration.
     *
     * @return A List containing the actual literals defined by this enumeration, this list
     *         can not be modified.
     */
    public static List<String> literals()
    {
        return PistolType.literals;
    }

    /**
     * Returns an unmodifiable list containing the names of the literals that are known
     * by this enumeration.
     *
     * @return A List containing the actual names of the literals defined by this
     *         enumeration, this list can not be modified.
     */
    public static List<String> names()
    {
        return PistolType.names;
    }

    private static Map<String, PistolType> values = new LinkedHashMap<String, PistolType>(2, 1);
    private static List<String> literals = new ArrayList<String>(2);
    private static List<String> names = new ArrayList<String>(2);
    private static List<PistolType> valueList = new ArrayList<PistolType>(2);

    /**
     * Initializes the values.
     */
    static
    {
        synchronized (PistolType.values)
        {
            PistolType.values.put(PISTOL1.enumValue, PISTOL1);
            PistolType.values.put(PISTOL2.enumValue, PISTOL2);
        }
        synchronized (PistolType.valueList)
        {
            PistolType.valueList.add(PISTOL1);
            PistolType.valueList.add(PISTOL2);
            PistolType.valueList = Collections.unmodifiableList(valueList);
        }
        synchronized (PistolType.literals)
        {
            PistolType.literals.add(PISTOL1.enumValue);
            PistolType.literals.add(PISTOL2.enumValue);
            PistolType.literals = Collections.unmodifiableList(literals);
        }
        synchronized (PistolType.names)
        {
            PistolType.names.add("PISTOL1");
            PistolType.names.add("PISTOL2");
            PistolType.names = Collections.unmodifiableList(names);
        }
    }
    // type-safe-enumeration-object java merge-point
}