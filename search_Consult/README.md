# search_Consult.c
### Functioning

This code main function reads two arguments from CLI, the input file path and output file path, respectively. Then appends it into a from-scratch-built doubly linked circular list that uses a dummy as sentinel node. Lastly, writes the data in the output file, based on the operation typed in the input file, which must present its content based on the following syntax:
```sh
{<ordination_code>, <info>}
{<ordination_code>, <info>}
            ...
{<ordination_code>, <info>}
<op_number>
```
>Where ordination_code must be a positive integer,
>info can be any information at all and
>operation number either 1, 2 or 3.

- 1 : prints the list in ascending order, based on ord-code
- 2 : prints the list in descending order
- 3: search for a code and its following info, then print. (Requires an extra line, containing the code to be searched)

