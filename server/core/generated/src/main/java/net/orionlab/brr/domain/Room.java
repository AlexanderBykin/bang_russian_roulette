// license-header java merge-point
//
// Attention: Generated code! Do not modify by hand!
// Generated by: hibernate/HibernateEntity.vsl in andromda-hibernate-cartridge.
//
package net.orionlab.brr.domain;

import java.io.Serializable;
import java.util.Collection;
import java.util.Date;
import java.util.HashSet;

/**
 * 
 */
// HibernateEntity.vsl annotations merge-point
public abstract class Room
    implements Serializable, Comparable<Room>
{
    /**
     * The serial version UID of this class. Needed for serialization.
     */
    private static final long serialVersionUID = -334631033928638415L;

    // Generate 12 attributes
    private RoomType roomType;

    /**
     * 
     * @return this.roomType RoomType
     */
    public RoomType getRoomType()
    {
        return this.roomType;
    }

    /**
     * 
     * @param roomTypeIn RoomType
     */
    public void setRoomType(RoomType roomTypeIn)
    {
        this.roomType = roomTypeIn;
    }

    private Integer bet = Integer.valueOf(0);

    /**
     * 
     * @return this.bet Integer
     */
    public Integer getBet()
    {
        return this.bet;
    }

    /**
     * 
     * @param betIn Integer
     */
    public void setBet(Integer betIn)
    {
        this.bet = betIn;
    }

    private Integer maxRounds = Integer.valueOf(0);

    /**
     * 
     * @return this.maxRounds Integer
     */
    public Integer getMaxRounds()
    {
        return this.maxRounds;
    }

    /**
     * 
     * @param maxRoundsIn Integer
     */
    public void setMaxRounds(Integer maxRoundsIn)
    {
        this.maxRounds = maxRoundsIn;
    }

    private Integer maxPlayers = Integer.valueOf(0);

    /**
     * 
     * @return this.maxPlayers Integer
     */
    public Integer getMaxPlayers()
    {
        return this.maxPlayers;
    }

    /**
     * 
     * @param maxPlayersIn Integer
     */
    public void setMaxPlayers(Integer maxPlayersIn)
    {
        this.maxPlayers = maxPlayersIn;
    }

    private Long playerBank = Long.valueOf(0);

    /**
     * 
     * @return this.playerBank Long
     */
    public Long getPlayerBank()
    {
        return this.playerBank;
    }

    /**
     * 
     * @param playerBankIn Long
     */
    public void setPlayerBank(Long playerBankIn)
    {
        this.playerBank = playerBankIn;
    }

    private Long investorBank = Long.valueOf(0);

    /**
     * 
     * @return this.investorBank Long
     */
    public Long getInvestorBank()
    {
        return this.investorBank;
    }

    /**
     * 
     * @param investorBankIn Long
     */
    public void setInvestorBank(Long investorBankIn)
    {
        this.investorBank = investorBankIn;
    }

    private Integer currentRound = Integer.valueOf(0);

    /**
     * 
     * @return this.currentRound Integer
     */
    public Integer getCurrentRound()
    {
        return this.currentRound;
    }

    /**
     * 
     * @param currentRoundIn Integer
     */
    public void setCurrentRound(Integer currentRoundIn)
    {
        this.currentRound = currentRoundIn;
    }

    private Boolean isGameStarted = Boolean.valueOf(false);

    /**
     * 
     * @return this.isGameStarted Boolean
     */
    public Boolean getIsGameStarted()
    {
        return this.isGameStarted;
    }

    /**
     * 
     * @param isGameStartedIn Boolean
     */
    public void setIsGameStarted(Boolean isGameStartedIn)
    {
        this.isGameStarted = isGameStartedIn;
    }

    private Date dateCreate;

    /**
     * 
     * @return this.dateCreate Date
     */
    public Date getDateCreate()
    {
        return this.dateCreate;
    }

    /**
     * 
     * @param dateCreateIn Date
     */
    public void setDateCreate(Date dateCreateIn)
    {
        this.dateCreate = dateCreateIn;
    }

    private Date dateEdit;

    /**
     * 
     * @return this.dateEdit Date
     */
    public Date getDateEdit()
    {
        return this.dateEdit;
    }

    /**
     * 
     * @param dateEditIn Date
     */
    public void setDateEdit(Date dateEditIn)
    {
        this.dateEdit = dateEditIn;
    }

    private Boolean isArchived = Boolean.valueOf(false);

    /**
     * 
     * @return this.isArchived Boolean
     */
    public Boolean getIsArchived()
    {
        return this.isArchived;
    }

    /**
     * 
     * @param isArchivedIn Boolean
     */
    public void setIsArchived(Boolean isArchivedIn)
    {
        this.isArchived = isArchivedIn;
    }

    private Long id;

    /**
     * 
     * @return this.id Long
     */
    public Long getId()
    {
        return this.id;
    }

    /**
     * 
     * @param idIn Long
     */
    public void setId(Long idIn)
    {
        this.id = idIn;
    }

    // Generate 1 associations
    private Collection<RoomRound> rounds = new HashSet<RoomRound>();

    /**
     * 
     * @return this.rounds Collection<RoomRound>
     */
    public Collection<RoomRound> getRounds()
    {
        return this.rounds;
    }

    /**
     * 
     * @param roundsIn Collection<RoomRound>
     */
    public void setRounds(Collection<RoomRound> roundsIn)
    {
        this.rounds = roundsIn;
    }

    /**
     * 
     * @param elementToAdd RoomRound
     * @return <tt>true</tt> if this collection changed as a result of the
     *         call
     */
    public boolean addRounds(RoomRound elementToAdd)
    {
        return this.rounds.add(elementToAdd);
    }

    /**
     * 
     * @param elementToRemove RoomRound
     * @return <tt>true</tt> if this collection changed as a result of the
     *         call
     */
    public boolean removeRounds(RoomRound elementToRemove)
    {
        return this.rounds.remove(elementToRemove);
    }

    /**
     * Returns <code>true</code> if the argument is an Room instance and all identifiers for this entity
     * equal the identifiers of the argument entity. Returns <code>false</code> otherwise.
     */
    @Override
    public boolean equals(Object object)
    {
        if (this == object)
        {
            return true;
        }
        if (!(object instanceof Room))
        {
            return false;
        }
        final Room that = (Room)object;
        if (this.id == null || that.getId() == null || !this.id.equals(that.getId()))
        {
            return false;
        }
        return true;
    }

    /**
     * Returns a hash code based on this entity's identifiers.
     */
    @Override
    public int hashCode()
    {
        int hashCode = 0;
        hashCode = 29 * hashCode + (this.id == null ? 0 : this.id.hashCode());

        return hashCode;
    }

    /**
     * Constructs new instances of {@link Room}.
     */
    public static final class Factory
    {
        /**
         * Constructs a new instance of {@link Room}.
         * @return new RoomImpl()
         */
        public static Room newInstance()
        {
            return new RoomImpl();
        }

        /**
         * Constructs a new instance of {@link Room}, taking all required and/or
         * read-only properties as arguments, except for identifiers.
         * @param roomType RoomType
         * @param dateCreate Date
         * @return newInstance
         */
        public static Room newInstance(RoomType roomType, Date dateCreate)
        {
            final Room entity = new RoomImpl();
            entity.setRoomType(roomType);
            entity.setDateCreate(dateCreate);
            return entity;
        }

        /**
         * Constructs a new instance of {@link Room}, taking all possible properties
         * (except the identifier(s))as arguments.
         * @param roomType RoomType
         * @param bet Integer
         * @param maxRounds Integer
         * @param maxPlayers Integer
         * @param playerBank Long
         * @param investorBank Long
         * @param currentRound Integer
         * @param isGameStarted Boolean
         * @param dateCreate Date
         * @param dateEdit Date
         * @param isArchived Boolean
         * @param rounds Collection<RoomRound>
         * @return newInstance Room
         */
        public static Room newInstance(RoomType roomType, Integer bet, Integer maxRounds, Integer maxPlayers, Long playerBank, Long investorBank, Integer currentRound, Boolean isGameStarted, Date dateCreate, Date dateEdit, Boolean isArchived, Collection<RoomRound> rounds)
        {
            final Room entity = new RoomImpl();
            entity.setRoomType(roomType);
            entity.setBet(bet);
            entity.setMaxRounds(maxRounds);
            entity.setMaxPlayers(maxPlayers);
            entity.setPlayerBank(playerBank);
            entity.setInvestorBank(investorBank);
            entity.setCurrentRound(currentRound);
            entity.setIsGameStarted(isGameStarted);
            entity.setDateCreate(dateCreate);
            entity.setDateEdit(dateEdit);
            entity.setIsArchived(isArchived);
            entity.setRounds(rounds);
            return entity;
        }
    }

    /**
     * @see Comparable#compareTo
     */
    public int compareTo(Room o)
    {
        int cmp = 0;
        if (this.getId() != null)
        {
            cmp = this.getId().compareTo(o.getId());
        }
        else
        {
            if (this.getRoomType() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getRoomType().compareTo(o.getRoomType()));
            }
            if (this.getBet() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getBet().compareTo(o.getBet()));
            }
            if (this.getMaxRounds() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getMaxRounds().compareTo(o.getMaxRounds()));
            }
            if (this.getMaxPlayers() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getMaxPlayers().compareTo(o.getMaxPlayers()));
            }
            if (this.getPlayerBank() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getPlayerBank().compareTo(o.getPlayerBank()));
            }
            if (this.getInvestorBank() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getInvestorBank().compareTo(o.getInvestorBank()));
            }
            if (this.getCurrentRound() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getCurrentRound().compareTo(o.getCurrentRound()));
            }
            if (this.getIsGameStarted() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getIsGameStarted().compareTo(o.getIsGameStarted()));
            }
            if (this.getDateCreate() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getDateCreate().compareTo(o.getDateCreate()));
            }
            if (this.getDateEdit() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getDateEdit().compareTo(o.getDateEdit()));
            }
            if (this.getIsArchived() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getIsArchived().compareTo(o.getIsArchived()));
            }
        }
        return cmp;
    }
// HibernateEntity.vsl merge-point
}