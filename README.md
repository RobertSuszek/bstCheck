# bstCheck

Program runs in CMD and checks if a given tree is a BST.
The tree must be given in text file, in XML-like format.

Example of txt file given to program:
<node=60>
  <node=41>
    <node=16>
      <node=25>
      </node>
    <node=53>
      <node=46>
        <node=42>
        </node>
      </node>
      <node=55>
      </node>
    </node>
    </node>
  </node>
  <node=71>
    <node=65>
      <node=63>
        <node=62>
        </node>
        <node=64>
        </node>
      </node>
      <node=70>
      </node>
    </node>
  </node>
</node>

Program takes path of text file as -i parameter run in CMD. 
Example usage: SprawdzenieDrzewa -i myTreeFile.txt

Program prints "To jest BST" if given tree is a BST, or "Nie, to nie jest BST" is it isn't.

Program were developed as a project for one of my classes at SUoT.
