#ifndef INCLUDE_git_tree_h__
#define INCLUDE_git_tree_h__

#include "common.h"
#include "oid.h"
#include "repository.h"

/**
 * @file git/tree.h
 * @brief Git tree parsing, loading routines
 * @defgroup git_tree Git tree parsing, loading routines
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL


/** Representation of each one of the entries in a tree object. */
typedef struct git_tree_entry git_tree_entry;

/** Representation of a tree object. */
typedef struct git_tree git_tree;

/**
 * Lookup a tree object from the repository.
 * The generated tree object is owned by the revision
 * repo and shall not be freed by the user.
 *
 * @param repo the repo to use when locating the tree.
 * @param id identity of the tree to locate.
 * @return the tree; NULL if the tree could not be created
 */
GIT_EXTERN(git_tree *) git_tree_lookup(git_repository *repo, const git_oid *id);

/**
 * Create a new in-memory git_tree.
 *
 * The tree object must be manually filled using
 * setter methods before it can be written to its
 * repository.
 *
 * @param repo The repository where the object will reside
 * @return the object if creation was possible; NULL otherwise
 */
GIT_EXTERN(git_tree *) git_tree_new(git_repository *repo);

/**
 * Get the id of a tree.
 * @param tree a previously loaded tree.
 * @return object identity for the tree.
 */
GIT_EXTERN(const git_oid *) git_tree_id(git_tree *tree);


/**
 * Get the number of entries listed in a tree
 * @param tree a previously loaded tree.
 * @return the number of entries in the tree
 */
GIT_EXTERN(size_t) git_tree_entrycount(git_tree *tree);

/**
 * Lookup a tree entry by its filename
 * @param tree a previously loaded tree.
 * @param filename the filename of the desired entry
 * @return the tree entry; NULL if not found
 */
GIT_EXTERN(git_tree_entry *) git_tree_entry_byname(git_tree *tree, const char *filename);

/**
 * Lookup a tree entry by its position in the tree
 * @param tree a previously loaded tree.
 * @param idx the position in the entry list
 * @return the tree entry; NULL if not found
 */
GIT_EXTERN(git_tree_entry *) git_tree_entry_byindex(git_tree *tree, int idx);

/**
 * Get the UNIX file attributes of a tree entry
 * @param entry a tree entry
 * @return attributes as an integer
 */
GIT_EXTERN(unsigned int) git_tree_entry_attributes(git_tree_entry *entry);

/**
 * Get the filename of a tree entry
 * @param entry a tree entry
 * @return the name of the file
 */
GIT_EXTERN(const char *) git_tree_entry_name(git_tree_entry *entry);

/**
 * Get the id of the object pointed by the entry
 * @param entry a tree entry
 * @return the oid of the object
 */
GIT_EXTERN(const git_oid *) git_tree_entry_id(git_tree_entry *entry);

/**
 * Convert a tree entry to the git_object it points too.
 * @param entry a tree entry
 * @return a reference to the pointed object in the repository
 */
GIT_EXTERN(git_object *) git_tree_entry_2object(git_tree_entry *entry);

/**
 * Add a new entry to a tree.
 *
 * This will mark the tree as modified; the new entry will
 * be written back to disk on the next git_object_write()
 *
 * @param tree Tree object to store the entry
 * @iparam id OID for the tree entry
 * @param filename Filename for the tree entry
 * @param attributes UNIX file attributes for the entry
 * @return 0 on success; otherwise error code
 */
GIT_EXTERN(int) git_tree_add_entry(git_tree *tree, const git_oid *id, const char *filename, int attributes);

/**
 * Remove an entry by its index.
 *
 * Index must be >= 0 and < than git_tree_entrycount().
 *
 * This will mark the tree as modified; the modified entry will
 * be written back to disk on the next git_object_write()
 *
 * @param tree Tree where to remove the entry
 * @param idx index of the entry
 * @return 0 on successful removal; GIT_ENOTFOUND if the entry wasn't found
 */
GIT_EXTERN(int) git_tree_remove_entry_byindex(git_tree *tree, int idx);

/**
 * Remove an entry by its filename.
 *
 * This will mark the tree as modified; the modified entry will
 * be written back to disk on the next git_object_write()
 *
 * @param tree Tree where to remove the entry
 * @param filename File name of the entry
 * @return 0 on successful removal; GIT_ENOTFOUND if the entry wasn't found
 */
GIT_EXTERN(int) git_tree_remove_entry_byname(git_tree *tree, const char *filename);

/**
 * Change the SHA1 id of a tree entry.
 *
 * This will mark the tree that contains the entry as modified;
 * the modified entry will be written back to disk on the next git_object_write()
 *
 * @param entry Entry object which will be modified
 * @param oid new SHA1 oid for the entry
 */
GIT_EXTERN(void) git_tree_entry_set_id(git_tree_entry *entry, const git_oid *oid);

/**
 * Change the filename of a tree entry.
 *
 * This will mark the tree that contains the entry as modified;
 * the modified entry will be written back to disk on the next git_object_write()
 *
 * @param entry Entry object which will be modified
 * @param oid new filename for the entry
 */
GIT_EXTERN(void) git_tree_entry_set_name(git_tree_entry *entry, const char *name);

/**
 * Change the attributes of a tree entry.
 *
 * This will mark the tree that contains the entry as modified;
 * the modified entry will be written back to disk on the next git_object_write()
 *
 * @param entry Entry object which will be modified
 * @param oid new attributes for the entry
 */
GIT_EXTERN(void) git_tree_entry_set_attributes(git_tree_entry *entry, int attr);

/** @} */
GIT_END_DECL
#endif
