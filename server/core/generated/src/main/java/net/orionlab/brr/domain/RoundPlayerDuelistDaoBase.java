// license-header java merge-point
//
// Attention: Generated code! Do not modify by hand!
// Generated by: hibernate/SpringHibernateDaoBase.vsl in andromda-spring-cartridge.
//
package net.orionlab.brr.domain;

import java.security.Principal;
import java.util.Collection;
import java.util.Date;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;
import net.orionlab.brr.PrincipalStore;
import net.orionlab.brr.PropertySearch;
import net.orionlab.brr.Search;
import org.andromda.spring.PaginationResult;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.collections.Transformer;
import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;
import org.springframework.orm.hibernate3.HibernateCallback;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

/**
 * <p>
 * Base Spring DAO Class: is able to create, update, remove, load, and find
 * objects of type <code>RoundPlayerDuelist</code>.
 * </p>
 *
 * @see RoundPlayerDuelist
 */
public abstract class RoundPlayerDuelistDaoBase
    extends HibernateDaoSupport
    implements RoundPlayerDuelistDao
{
    /**
     * {@inheritDoc}
     */
    @Override
    public Object get(final int transform, final Long id)
    {
        if (id == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.get - 'id' can not be null");
        }
        final Object entity = this.getHibernateTemplate().get(RoundPlayerDuelistImpl.class, id);
        return transformEntity(transform, (RoundPlayerDuelist)entity);
    }
    /**
     * {@inheritDoc}
     */
    @Override
    public RoundPlayerDuelist get(Long id)
    {
        return (RoundPlayerDuelist)this.get(TRANSFORM_NONE, id);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Object load(final int transform, final Long id)
    {
        if (id == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.load - 'id' can not be null");
        }
        final Object entity = this.getHibernateTemplate().get(RoundPlayerDuelistImpl.class, id);
        return transformEntity(transform, (RoundPlayerDuelist)entity);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public RoundPlayerDuelist load(Long id)
    {
        return (RoundPlayerDuelist)this.load(TRANSFORM_NONE, id);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    @SuppressWarnings({"unchecked"})
    public Collection<RoundPlayerDuelist> loadAll()
    {
        return (Collection<RoundPlayerDuelist>) this.loadAll(RoundPlayerDuelistDao.TRANSFORM_NONE);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Collection<?> loadAll(final int transform)
    {
        return this.loadAll(transform, -1, -1);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Collection<?> loadAll(final int pageNumber, final int pageSize)
    {
        return this.loadAll(RoundPlayerDuelistDao.TRANSFORM_NONE, pageNumber, pageSize);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Collection<?> loadAll(final int transform, final int pageNumber, final int pageSize)
    {
        try
        {
            final Criteria criteria = this.getSession(false).createCriteria(RoundPlayerDuelistImpl.class);
            if (pageNumber > 0 && pageSize > 0)
            {
                criteria.setFirstResult(this.calculateFirstResult(pageNumber, pageSize));
                criteria.setMaxResults(pageSize);
            }
            final Collection<?> results = criteria.list();
            this.transformEntities(transform, results);
            return results;
        }
        catch (HibernateException ex)
        {
            throw super.convertHibernateAccessException(ex);
        }
    }

    /**
     * firstResult = (pageNumber - 1) * pageSize
     * @param pageNumber
     * @param pageSize
     * @return firstResult
     */
    protected int calculateFirstResult(int pageNumber, int pageSize)
    {
        int firstResult = 0;
        if (pageNumber > 0)
        {
            firstResult = (pageNumber - 1) * pageSize;
        }
        return firstResult;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public RoundPlayerDuelist create(RoundPlayerDuelist roundPlayerDuelist)
    {
        return (RoundPlayerDuelist)this.create(RoundPlayerDuelistDao.TRANSFORM_NONE, roundPlayerDuelist);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Object create(final int transform, final RoundPlayerDuelist roundPlayerDuelist)
    {
        if (roundPlayerDuelist == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.create - 'roundPlayerDuelist' can not be null");
        }
        this.getHibernateTemplate().save(roundPlayerDuelist);
        return this.transformEntity(transform, roundPlayerDuelist);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    @SuppressWarnings({"unchecked"})
    public Collection<RoundPlayerDuelist> create(final Collection<RoundPlayerDuelist> entities)
    {
        return (Collection<RoundPlayerDuelist>) create(RoundPlayerDuelistDao.TRANSFORM_NONE, entities);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Collection<?> create(final int transform, final Collection<RoundPlayerDuelist> entities)
    {
        if (entities == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.create - 'entities' can not be null");
        }
        this.getHibernateTemplate().executeWithNativeSession(
            new HibernateCallback()
            {
                public Object doInHibernate(Session session)
                    throws HibernateException
                {
                    for (RoundPlayerDuelist entity : entities)
                    {
                        create(transform, entity);
                    }
                    return null;
                }
            });
        return entities;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public RoundPlayerDuelist create(
        Integer pos,
        Boolean isDuelist,
        Long winAmount,
        Date dateCreate,
        Date dateEdit,
        Boolean isArchived)
    {
        return (RoundPlayerDuelist)this.create(RoundPlayerDuelistDao.TRANSFORM_NONE, pos, isDuelist, winAmount, dateCreate, dateEdit, isArchived);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Object create(
        final int transform,
        Integer pos,
        Boolean isDuelist,
        Long winAmount,
        Date dateCreate,
        Date dateEdit,
        Boolean isArchived)
    {
        RoundPlayerDuelist entity = new RoundPlayerDuelistImpl();
        entity.setPos(pos);
        entity.setIsDuelist(isDuelist);
        entity.setWinAmount(winAmount);
        entity.setDateCreate(dateCreate);
        entity.setDateEdit(dateEdit);
        entity.setIsArchived(isArchived);
        return this.create(transform, entity);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public RoundPlayerDuelist create(
        Date dateCreate,
        RoomRound round)
    {
        return (RoundPlayerDuelist)this.create(RoundPlayerDuelistDao.TRANSFORM_NONE, dateCreate, round);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Object create(
        final int transform,
        Date dateCreate,
        RoomRound round)
    {
        RoundPlayerDuelist entity = new RoundPlayerDuelistImpl();
        entity.setDateCreate(dateCreate);
        entity.setRound(round);
        return this.create(transform, entity);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void update(RoundPlayerDuelist roundPlayerDuelist)
    {
        if (roundPlayerDuelist == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.update - 'roundPlayerDuelist' can not be null");
        }
        this.getHibernateTemplate().update(roundPlayerDuelist);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void update(final Collection<RoundPlayerDuelist> entities)
    {
        if (entities == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.update - 'entities' can not be null");
        }
        this.getHibernateTemplate().executeWithNativeSession(
            new HibernateCallback()
            {
                public Object doInHibernate(Session session)
                    throws HibernateException
                {
                    for (RoundPlayerDuelist entity : entities)
                    {
                        update(entity);
                    }
                    return null;
                }
            });
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void remove(RoundPlayerDuelist roundPlayerDuelist)
    {
        if (roundPlayerDuelist == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.remove - 'roundPlayerDuelist' can not be null");
        }
        this.getHibernateTemplate().delete(roundPlayerDuelist);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void remove(Long id)
    {
        if (id == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.remove - 'id' can not be null");
        }
        RoundPlayerDuelist entity = this.get(id);
        if (entity != null)
        {
            this.remove(entity);
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void remove(Collection<RoundPlayerDuelist> entities)
    {
        if (entities == null)
        {
            throw new IllegalArgumentException(
                "RoundPlayerDuelist.remove - 'entities' can not be null");
        }
        this.getHibernateTemplate().deleteAll(entities);
    }
    /**
     * Allows transformation of entities into value objects
     * (or something else for that matter), when the <code>transform</code>
     * flag is set to one of the constants defined in <code>RoundPlayerDuelistDao</code>, please note
     * that the {@link #TRANSFORM_NONE} constant denotes no transformation, so the entity itself
     * will be returned.
     *
     * If the integer argument value is unknown {@link #TRANSFORM_NONE} is assumed.
     *
     * @param transform one of the constants declared in {@link RoundPlayerDuelistDao}
     * @param entity an entity that was found
     * @return the transformed entity (i.e. new value object, etc)
     * @see RoundPlayerDuelistDao#transformEntity(int, RoundPlayerDuelist)
     */
    public Object transformEntity(final int transform, final RoundPlayerDuelist entity)
    {
        Object target = null;
        if (entity != null)
        {
            switch (transform)
            {
                case RoundPlayerDuelistDao.TRANSFORM_NONE : // fall-through
                default:
                    target = entity;
            }
        }
        return target;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void transformEntities(final int transform, final Collection<?> entities)
    {
        switch (transform)
        {
            case RoundPlayerDuelistDao.TRANSFORM_NONE : // fall-through
                default:
                // do nothing;
        }
    }

    /**
     * @see RoundPlayerDuelistDao#toEntities(Collection)
     */
    public void toEntities(final Collection<?> results)
    {
        if (results != null)
        {
            CollectionUtils.transform(results, this.ENTITYTRANSFORMER);
        }
    }

    /**
     * This anonymous transformer is designed to transform report query results
     * (which result in an array of entities) to {@link RoundPlayerDuelist}
     * using the Jakarta Commons-Collections Transformation API.
     */
    private Transformer ENTITYTRANSFORMER =
        new Transformer()
        {
            public Object transform(Object input)
            {
                Object result = null;
                if (input instanceof Object[])
                {
                    result = toEntity((Object[])input);
                }
                else if (input instanceof RoundPlayerDuelist)
                {
                    result = input;
                }
                return result;
            }
        };

    /**
     * @param row
     * @return RoundPlayerDuelist
     */
    protected RoundPlayerDuelist toEntity(Object[] row)
    {
        RoundPlayerDuelist target = null;
        if (row != null)
        {
            final int numberOfObjects = row.length;
            for (int ctr = 0; ctr < numberOfObjects; ctr++)
            {
                final Object object = row[ctr];
                if (object instanceof RoundPlayerDuelist)
                {
                    target = (RoundPlayerDuelist)object;
                    break;
                }
            }
        }
        return target;
    }

    /**
     * Gets the current <code>principal</code> if one has been set,
     * otherwise returns <code>null</code>.
     *
     * @return the current principal
     */
    protected Principal getPrincipal()
    {
        return PrincipalStore.get();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    @SuppressWarnings({ "unchecked" })
    public PaginationResult search(final int transform, final int pageNumber, final int pageSize, final Search search)
    {
        try
        {
            search.setPageNumber(pageNumber);
            search.setPageSize(pageSize);
            final PropertySearch propertySearch = new PropertySearch(
                this.getSession(false), RoundPlayerDuelistImpl.class, search);
            final List results = propertySearch.executeAsList();
            this.transformEntities(transform, results);
            return new PaginationResult(results.toArray(new Object[results.size()]), propertySearch.getTotalCount());
        }
        catch (HibernateException ex)
        {
            throw super.convertHibernateAccessException(ex);
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public PaginationResult search(final int pageNumber, final int pageSize, final Search search)
    {
        return this.search(RoundPlayerDuelistDao.TRANSFORM_NONE, pageNumber, pageSize, search);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Set<?> search(final int transform, final Search search)
    {
        try
        {
            final PropertySearch propertySearch = new PropertySearch(
                this.getSession(false), RoundPlayerDuelistImpl.class, search);
            final Set<?> results = propertySearch.executeAsSet();
            this.transformEntities(transform, results);
            return results;
        }
        catch (HibernateException ex)
        {
            throw super.convertHibernateAccessException(ex);
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    @SuppressWarnings("unchecked")
    public Set<RoundPlayerDuelist> search(final Search search)
    {
        return (Set<RoundPlayerDuelist>) this.search(RoundPlayerDuelistDao.TRANSFORM_NONE, search);
    }

    /**
     * Executes and returns the given Hibernate queryObject as a {@link PaginationResult} instance.
     * @param queryObject
     * @param transform
     * @param pageNumber
     * @param pageSize
     * @return PaginationResult
     */
    @SuppressWarnings({ "unchecked" })
    protected PaginationResult getPaginationResult(
        final Query queryObject,
        final int transform, int pageNumber, int pageSize)
    {
        try
        {
            final ScrollableResults scrollableResults = queryObject.scroll();
            scrollableResults.last();
            int totalCount = scrollableResults.getRowNumber();
            totalCount = totalCount >= 0 ? totalCount + 1 : 0;
            if (pageNumber > 0 && pageSize > 0)
            {
                queryObject.setFirstResult(this.calculateFirstResult(pageNumber, pageSize));
                queryObject.setMaxResults(pageSize);
            }
            // Unchecked transformation because Set object is reused, cannot be strongly typed.
            Set results = new LinkedHashSet(queryObject.list());
            transformEntities(transform, results);
            return new PaginationResult(results.toArray(new Object[results.size()]), totalCount);
        }
        catch (HibernateException ex)
        {
            throw super.convertHibernateAccessException(ex);
        }
    }

    // spring-hibernate-dao-base merge-point
}