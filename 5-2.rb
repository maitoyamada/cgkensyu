input_file = 'bunny.ply'
output_file = 'output.obj'

vertices = []
faces = []

File.open(input_file, 'r') do |file|
  file.each_line do |line|
    if line.start_with?('element vertex')
      num_vertices = line.split(' ')[2].to_i
      num_vertices.times do
        vertex = file.readline.split.map(&:to_f)
        vertices << vertex
      end
    elsif line.start_with?('element face')
      num_faces = line.split(' ')[2].to_i
      num_faces.times do
        face = file.readline.split.map(&:to_i)
        faces << face
      end
    end
  end
end

File.open(output_file, 'w') do |file|
  vertices.each do |vertex|
    file.write("v #{vertex[0]} #{vertex[1]} #{vertex[2]}\n")
  end

  faces.each do |face|
    file.write("f #{face[1] + 1} #{face[2] + 1} #{face[3] + 1}\n")
  end
end
